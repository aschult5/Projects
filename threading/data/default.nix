{ system ? builtins.currentSystem, doCheck ? false }:

with import <nixpkgs> { inherit system; };

stdenv.mkDerivation rec {
   inherit doCheck;

   name = "data";
   src = ./.;

   buildInputs = [ libtool autoconf autoconf-archive automake gcc gtest ];

   preConfigure = ''
      libtoolize
      aclocal
      autoheader
      autoconf
      automake --add-missing
   '';

   hardeningDisable = [ "all" ];
}
