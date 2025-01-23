{
  description = "A blazing-fast CLI tool to efficiently manage your todos directly from the terminal";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
  }: let
    systems = [
      "aarch64-linux"
      "aarch64-darwin"
      "x86_64-darwin"
      "x86_64-linux"
    ];

    forAllSystems = f:
      nixpkgs.lib.genAttrs systems (system: let
        pkgs = import nixpkgs {inherit system;};
      in
        f pkgs system);
  in {
    devShells = forAllSystems (pkgs: system: {
      default = pkgs.mkShell {
        buildInputs = with pkgs; [
          clang
          gnumake
          fmt_11
          cxxopts
          bear
        ];
        shellHook = ''
          export SHELL=${pkgs.bashInteractive}
          export LIB_FMT=${pkgs.fmt_11.dev}
          export LIB_CXXOPTS=${pkgs.cxxopts}
        '';
      };
    });
    formatter = forAllSystems (pkgs: system: pkgs.alejandra);
  };
}
