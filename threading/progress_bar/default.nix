{ system ? builtins.currentSystem, doCheck ? true }:

with import <nixpkgs> { inherit system; };

stdenv.mkDerivation rec {
   inherit doCheck;

   name = "progress_bar";
   src = ./.;

   buildInputs = [ libtool autoconf autoconf-archive automake gcc gtest ];

   preConfigure = ''
      libtoolize
      aclocal
      autoheader
      autoconf
      automake --add-missing
   '';
}
