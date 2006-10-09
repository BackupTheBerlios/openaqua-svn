#!/usr/bin/perl -w

print "hallo\n";

sub BaseName {
   chomp;
   s/[.a-zA-Z0-9_]*$//;
   $_ = $&;
   return $_;
}

while ( <STDIN>){
   print BaseName . "\n";
}