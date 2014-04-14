#!/usr/bin/perl
package main;
use v5.10;

########################################################################
# Copyright 2014 RCF                                                   #
#                                                                      #
# Licensed under the Apache License, Version 2.0 (the "License");      #
# you may not use this file except in compliance with the License.     #
# You may obtain a copy of the License at                              #
#                                                                      #
#     http://www.apache.org/licenses/LICENSE-2.0                       #
#                                                                      #
# Unless required by applicable law or agreed to in writing,           #
# software distributed under the License is distributed on an          #
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,         #
# either express or implied.                                           #
# See the License for the specific language governing permissions      #
# and limitations under the License.                                   #
########################################################################

# Adding modules in @INC
use FindBin qw($Bin);
use lib "$Bin";

# Pragmas
use strict;
use warnings;

# Packages
use Cortex;
use Quark::Prog;
use Quark::Namespace qw(make_header make_source);

# Libraries
use Term::ANSIColor qw(:constants);

# Options
use Getopt::Long;

my $base    = "$Bin/..";
my $src     = "src";
my $inc     = "include";
my $help    = undef; 
my $build   = "build";
my $itemdir = "$base/$src/stk/item";

Getopt::Long::Configure('bundling');
GetOptions(
    "b|build-path=s"  => \$build,
    "i|item-path=s"   => \$itemdir,
    "h|help"          => \$help,
    "r|root-path=s"   => \$base,
    "s|src-path=s"    => \$src,
    "h|header-path=s" => \$inc,
);

my $srcdir  = "$base/$src/quark";
my $incdir  = "$base/$inc/quark";

sub make_subdir
{
    my $path = shift;
    return unless $path;
    my $subpath = $path =~ s|(.*)/.*?/|$1/|r;
    
    # Recursive call
    &make_subdir($subpath);
    
    mkdir $path;
}
# &make_subdir("$srcdir/");
# &make_subdir("$incdir/");

# Help/Usage
die << "HELP" if($help);

 parser.pl
 --------------------
 Creates a package in Java for runngin a 
 program in assembly, loaded by Main.java
 
 OPTIONS:
 * -b, --build-path=s
   Path/Directory for .class files.
 * -r, --root-path=s
   Root directory for all the process.
 * -s, --src-path=s
   Path/Directory for .java files.

 AUTHORS
 Renato Cordeiro Ferreira.

HELP

#######################################################################
##                             PARSING                               ##
#######################################################################
for my $file (@ARGV)
{
    print " Generating C++ files for ", BOLD, "$file...", RESET;
    
    # Create parser and program
    my $positronic_brain = new Cortex;
    my @prog = $positronic_brain->parse("$file");
    
    # Output a .cpp and .hpp files 
    # for the assembly program
    my $prog = new Quark::Prog (
        FILE    => $file, 
        PROG    => \@prog,
        INCDIR  => $incdir,
        SRCDIR  => $srcdir,
        ITEMDIR => $itemdir
    );
    $prog->make_header();
    $prog->make_source();
    
    print BOLD, GREEN, "\r[OK] ", RESET;
    print "Generating C++ files for ", BOLD, "$file\n", RESET;
}

# Create namespace info
print BOLD, YELLOW, "Generating C++ files for namespace ";
print BOLD, GREEN,  "Quark...", RESET;

Quark::Namespace::make_header($incdir, $srcdir);
Quark::Namespace::make_source($incdir, $srcdir);

print BOLD, GREEN, "\r[OK] ", RESET;
print BOLD, YELLOW, "Generating C++ files for namespace ", RESET;
print BOLD, GREEN,  "Quark\n", RESET;
