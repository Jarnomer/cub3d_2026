{
  description = "cub3D Development Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      ...
    }@inputs:
    inputs.flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc
            gnumake
            mlx42
            glfw
            valgrind
            norminette
            gdb
          ];

          shellHook = ''
            printf "\033[35mcub3D development environment loaded!\033[0m\n"
            trap 'make fclean 2>/dev/null' EXIT
          '';
        };
      }
    );
}
