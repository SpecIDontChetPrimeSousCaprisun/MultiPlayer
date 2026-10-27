{ nixpkgs, ... }:
let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
    mingw = pkgs.pkgsCross.mingwW64;
in {
    languages.cplusplus.enable = true;

    packages = with pkgs; [
	gcc
	glfw
	gdb
	libX11
	libXrandr
	libXi
	libXxf86vm
	libXcursor
	enet
	mingw.buildPackages.gcc
	mingw.glfw
    ];
}
