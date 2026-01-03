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
            # Build tools
            cmake
            gcc
            gnumake
            
            # Graphics
            mlx42
            glfw
            
            # Development
            valgrind
            norminette
            gdb
            
            # Threading
            perf
          ];

          shellHook = ''
            printf "\033[35mcub3D development environment loaded!\033[0m\n"
            trap 'make fclean 2>/dev/null' EXIT
          '';
        };
      }
    );
}
