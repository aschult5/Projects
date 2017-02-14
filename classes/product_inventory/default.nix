{ system ? builtins.currentSystem }:

with import <nixpkgs> { inherit system; };

stdenv.mkDerivation rec {
   name = "product_inventory";
   src = ./.;

   buildInputs = [ autoconf autoconf-archive automake gcc ];

   preConfigure = ''
      aclocal
      autoheader
      autoconf
      automake --add-missing
   '';
}

