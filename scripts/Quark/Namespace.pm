#!/usr/bin/perl
package Quark::Namespace;
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

# Pragmas
use strict;
use warnings;

use Exporter 'import'; # gives you Exporter's import() method directly
our @EXPORT_OK = qw(make_header make_source); 

########################################################################
##                          DEFAULT CPP CODE                          ##
########################################################################

my $COPYRIGHT = << 'COPYRIGHT';
/**********************************************************************/
/* Copyright 2014 RCF                                                 */ 
/*                                                                    */
/* Licensed under the Apache License, Version 2.0 (the "License");    */
/* you may not use this file except in compliance with the License.   */
/* You may obtain a copy of the License at                            */
/*                                                                    */
/*     http://www.apache.org/licenses/LICENSE-2.0                     */
/*                                                                    */
/* Unless required by applicable law or agreed to in writing,         */
/* software distributed under the License is distributed on an        */
/* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,       */
/* either express or implied.                                         */
/* See the License for the specific language governing permissions    */
/* and limitations under the License.                                 */
/**********************************************************************/
COPYRIGHT

## QUARK HPP ############################################################
my $quark_hpp_init = << "QUARK_HPP_INIT";
$COPYRIGHT
#ifndef HPP_QUARK_DEFINED
#define HPP_QUARK_DEFINED

// Default libraries
#include <string>
#include <unordered_map>

// Libraries
#include "Command.hpp"

// Auto-Generated Libraries
QUARK_HPP_INIT

my $quark_hpp_end = << "QUARK_HPP_END";

// Mapping strings in functions
namespace quark 
{
    typedef vm::Prog (*Func_ptr)();
    extern std::unordered_map<std::string,Func_ptr> functions;
}

#endif
QUARK_HPP_END

## QUARK CPP ############################################################
my $quark_cpp_init = << "QUARK_CPP_INIT";
$COPYRIGHT
// Libraries
#include "Quark.hpp"
using namespace quark;

std::unordered_map<std::string,Func_ptr> quark::functions
{
QUARK_CPP_INIT

my $quark_cpp_end = << "QUARK_CPP_END";
};
QUARK_CPP_END

########################################################################
##                    PRINTING NAMESPACE ACCESSORS                    ##
########################################################################

sub make_header
{
    return if scalar @_ != 2;
    my $incdir = shift;
    my $srcdir = shift;
    
    # Get all .hpp inside $incdir directory
    my @incs = get_includes($incdir);

    # Create a Quark.hpp header file
    open(my $QUARK_HPP, ">", "$incdir/Quark.hpp")
        or die "Unable to open new file $incdir/Quark.hpp";

    select $QUARK_HPP;
    print $quark_hpp_init;
    
    # Print included files
    map { say "#include \"$_\"" } @incs;
    
    print $quark_hpp_end;
    select STDOUT;
    
    close $QUARK_HPP;
}

sub make_source
{
    return if scalar @_ != 2;
    my $incdir = shift;
    my $srcdir = shift;
    
    # Get all .hpp inside $incdir directory
    my @incs = get_includes($incdir);
    map { s/(.*)\.hpp/$1/ } @incs;

    # Get maximum size of include
    my $max_length = 0;
    map { (length($_) > $max_length) ? ($max_length = length($_)) : () } @incs;
    
    # Create a Quark.cpp source file
    open(my $QUARK_CPP, ">", "$srcdir/Quark.cpp")
        or die "Unable to open new file $srcdir/Quark.cpp";

    select $QUARK_CPP;
    print $quark_cpp_init;
    
    # Create map of function names to strings
    for (sort { length($a) <=> length($b) } @incs)
    {
        print " " x 4, "{ ";
        printf "%-*s", $max_length+2, "\"$_\"";     # +2 from \" \"
        print ", ";
        printf "%-*s", $max_length+8, "&upload_$_"; # +8 from &upload_
        say " },";
    }

    print $quark_cpp_end;
    select STDOUT;
    
    close $QUARK_CPP;
}

sub get_includes
{
    return if scalar @_ != 1;
    my $incdir = shift;
    
    # Get all .hpp inside $incdir directory
    opendir INCLUDES, $incdir;
    my @incs = grep { 
        not /^\./ and not /Quark\.hpp/ and -f "$incdir/$_" 
    } readdir INCLUDES;
    closedir INCLUDES;
    
    return @incs;
}
