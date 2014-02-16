#!/usr/bin/perl
package Quark::Prog;
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

# Function to evaluate if a scalar is a number (or not)
use Scalar::Util qw(looks_like_number); 

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
    
my $PROG_HEADER = << "PROG_HEADER";
$COPYRIGHT
#ifndef HPP_#BASENAME#_DEFINED
#define HPP_#BASENAME#_DEFINED

// Libraries
#include "Command.hpp"

namespace parser {
namespace quark {
    
    vm::Prog upload_#BASENAME#();
    
}}

#endif
PROG_HEADER

my $PROG_SOURCE_INIT = << "PROG_SOURCE_INIT";
$COPYRIGHT
// Default Libraries
#include <vector>
#include <iostream>

// Libraries
//#include "Stk.hpp"
#include "Text.hpp"
#include "Number.hpp"
#include "Address.hpp"
#include "Stackable.hpp"
#include "#BASENAME#.hpp"
using namespace stk;

/**
 * <b>Parser for program #FILE#.</b>
 * This file is automatically 
 * generated by parser.pl
 * \@author parser.pl
 */
vm::Prog parser::quark::upload_#BASENAME#()
{
    using namespace vm;
    vm::Prog PROG;
PROG_SOURCE_INIT

my $PROG_SOURCE_END = << "PROG_SOURCE_END";

    return PROG;
}
PROG_SOURCE_END

########################################################################
##                            CONSTRUCTOR                             ##
########################################################################

sub new
{
    my $invocant = shift;
    my $class = ref($invocant) || $invocant;
    
    my $obj = 
    {
        FILE      => "",
        PROG      => [],
        SRCDIR    => ".",
        INCDIR    => ".",
        ITEMDIR   => ".",
        ITEM      => {},
        VARS      => {},
        ATTACK    => {},
        ADDRESS   => {},
        TEXTUAL   => {},
        NUMERIC   => {},
        DIRECTION => {},
        MAX_COM   => 0, # null
        MAX_ARG   => 0, # null
        MAX_LAB   => 0, # null
        @_
    };
    
    $obj->{BASENAME} = $obj->{FILE};
    $obj->{BASENAME} =~ s|(?:.*/)?(.*)\..*|$1|;
    $obj->{BASENAME} = ucfirst lc $obj->{BASENAME};
    
    $obj->{PROG_HEADER}      =  $PROG_HEADER;
    $obj->{PROG_HEADER}      =~ s/#BASENAME#/$obj->{BASENAME}/g;
    
    $obj->{PROG_SOURCE_INIT} =  $PROG_SOURCE_INIT;
    $obj->{PROG_SOURCE_INIT} =~ s/#FILE#/$obj->{FILE}/g;
    $obj->{PROG_SOURCE_INIT} =~ s/#BASENAME#/$obj->{BASENAME}/g;
    
    $obj->{PROG_SOURCE_END}  =  $PROG_SOURCE_END;
    $obj->{PROG_SOURCE_END}  =~ s/#BASENAME#/$obj->{BASENAME}/g;
    
    bless $obj, $class;
    $obj->preproc();
    
    return $obj;
}

########################################################################
##                              METHODS                               ##
########################################################################
sub make_header
{
    # Get object for the method
    my $obj = shift;
    
    open(my $PARSER_HPP, ">", "$obj->{INCDIR}/$obj->{BASENAME}.hpp")
        or die "Unable to open new file $obj->{INCDIR}/$obj->{BASENAME}.hpp";
    
    select $PARSER_HPP;
    print $obj->{PROG_HEADER};
    select STDOUT;
}

sub make_source
{
    # Get object for the method
    my $obj = shift;
    
    open(my $PARSER_CPP, ">", "$obj->{SRCDIR}/$obj->{BASENAME}.cpp")
        or die "Unable to open new file $obj->{SRCDIR}/$obj->{BASENAME}.cpp";

    select $PARSER_CPP;
    say $obj->{PROG_SOURCE_INIT};

    # Print sorted numerical, textual, direction and stackable variables
    if(scalar keys %{$obj->{ADDRESS}}) 
    {
        my %address_numeric;
        
        while(my ($key, $value) = each %{$obj->{ADDRESS}})
        {
            my ($var, $address) = ($value->[0], $value->[1]);
            $address_numeric{$var} = $address;
        }   
        
        say " " x 4, "// Address variables";
        for my $var (sort keys %address_numeric) 
        { say " " x 4, $address_numeric{$var}; }
        print "\n";
    }

    if(scalar keys %{$obj->{NUMERIC}}) 
    {
        my %numbered_numeric;
        
        while(my ($key, $value) = each %{$obj->{NUMERIC}})
        {
            my ($var, $number) = ($value->[0], $value->[1]);
            $numbered_numeric{$var} = $number;
        }   
        
        say " " x 4, "// Numerical variables";
        for my $var (sort keys %numbered_numeric) 
        { say " " x 4, $numbered_numeric{$var}; }
        print "\n";
    }

    if(scalar keys %{$obj->{VARS}})
    {
        say " " x 4, "// Assembly's local variables";
        for my $var (sort keys %{$obj->{VARS}}) 
        { say " " x 4, $obj->{VARS}{$var}[1]; }
        print "\n";
    }

    if(scalar keys %{$obj->{TEXTUAL}})
    {
        say " " x 4, "// Textual variables";
        for my $txt (sort keys %{$obj->{TEXTUAL}}) 
        { say " " x 4, $obj->{TEXTUAL}{$txt}[1]; }
        print "\n";
    }

    if(scalar keys %{$obj->{DIRECTION}})
    {
        say " " x 4, "// Direction variables";
        for my $dir (sort keys %{$obj->{DIRECTION}}) 
        { say " " x 4, $obj->{DIRECTION}{$dir}; }
        print "\n";
    }

    if(scalar keys %{$obj->{ATTACK}})
    {
        say " " x 4, "// Attack variables";
        for my $att (sort keys %{$obj->{ATTACK}}) 
        { say " " x 4, $obj->{ATTACK}{$att}; }
        print "\n";
    }

    # Printing items (if used)
    while(my ($key, $value) = each %{$obj->{ITEM}})
    {
        next if not $obj->{ITEM}{$key}; # No items found
        
        my $class = ucfirst $key;
        my $object = uc $key;
        
        say " " x 4, "// $class variable";
        say " " x 4, "$class $object = new $class();";
        print "\n";
    }

    # Printing program
    for my $line (@{$obj->{PROG}})
    {
        print " " x 4; 
        print "PROG.push_back( vm::Command { ";
        (defined $line->[0]) 
            ? (printf   "Command::Opcode::%-*s", $obj->{MAX_COM}, "$line->[0]") 
            : (printf   "                 %-*s", $obj->{MAX_COM}, "");
        (defined $line->[1]) 
            ? (printf ", %-*s", $obj->{MAX_ARG}, "$line->[1]") 
            : (printf "  %-*s", $obj->{MAX_ARG}, ""); 
        if($obj->{MAX_LAB} != 0)
        {
        (defined $line->[2]) 
            ? (printf ", \"%-*s\"", $obj->{MAX_LAB}, "$line->[2]")
            : (printf "   %-*s ", $obj->{MAX_LAB}, ""); 
        }
        print " });";
        
        print "\n";
    }

    say $obj->{PROG_SOURCE_END};
    select STDOUT;

    close $PARSER_CPP;
}

########################################################################
##                          AUXILIAR METHODS                          ##
########################################################################

sub preproc
{
    # Get object for the method
    my $obj = shift;

    # Get items from item directory
    opendir ITEMS, $obj->{ITEMDIR};
    map  { s/\.cpp//; $obj->{ITEM}{$_} = 0 } 
    grep { not /^\./ and not /^Item/ and -f "$obj->{ITEMDIR}/$_"} readdir ITEMS;
    closedir ITEMS;
    
    my ($t, $n, $a, $v) = (0, 0, 0, 0);
    for my $line (@{$obj->{PROG}})
    {
        next if not defined $line;
        
        # Split line fields
        my ($func, $arg, $label) = @$line;
        
        # Calculate maximum function and label
        # (each +2 are came from the double quotes)
        if(defined $func and $obj->{MAX_COM} < length($func))
        { $obj->{MAX_COM} = length($func); }
        
        if(defined $label and $obj->{MAX_LAB} < length($label))
        { $obj->{MAX_LAB} = length($label); }
        
        # Creating variables
        if(defined $arg)
        {
            # Address argument
            if($arg =~ /^ADDRESS\(&(\d+)\)/)
            {
                $arg = $1;
                if(not exists $obj->{ADDRESS}{$arg})
                {
                    $a++; $line->[1] = "adr$a";
                    $obj->{ADDRESS}{$arg} = 
                        [ $a, "Stackable_ptr adr$a { new Address { $arg } };" ];
                }
                else { $line->[1] = "adr$obj->{ADDRESS}{$arg}[0]"; }
            }
            
            # Numeric argument
            elsif( looks_like_number($arg) )
            {
                if(not exists $obj->{NUMERIC}{$arg})
                {
                    $n++; $line->[1] = "num$n";
                    $obj->{NUMERIC}{$arg} = 
                        [ $n, "Stackable_ptr num$n { new Number { $arg } };" ];
                }
                else { $line->[1] = "num$obj->{NUMERIC}{$arg}[0]"; }
            }
            
            # Direction
            elsif($arg =~ /^->/)
            {
                $arg = uc $arg; 
                $arg =~ s/->//; 
                $line->[1] = "d$arg";
                $obj->{DIRECTION}{$arg} 
                    = "Stackable_ptr d$arg { new Direction { \"$arg\" } };";
            }
            
            # Attack argument
            elsif($arg =~ /^\(x\)(\w+)$/)
            {
                $arg = uc $arg; 
                $arg =~ s/\(X\)//; 
                $line->[1] = "x$arg";
                $obj->{ATTACK}{$arg} 
                    = "Stackable_ptr x$arg { new Attack { \"$arg\" } };";
            }
            
            # Stackable (item) argument
            elsif($arg =~ /^{(\w+)}$/)
            {
                while(my ($key, $value) = each %{$obj->{ITEM}})
                {
                    my $stk = lc $1;
                    if($stk =~ /$key/i) 
                        { $obj->{ITEM}{$key} = 1; $line->[1] = uc $key; }
                }
            }
            
            # Variable name argument
            elsif($arg =~ /^\[(\w+)\]$/)
            {
                if(not exists $obj->{VARS}{$arg})
                {
                    $v++; $line->[1] = "var$v";
                    $obj->{VARS}{$arg} = 
                        [ $v, "Stackable_ptr var$v { new stk::Text { \"$arg\" } };" ];
                }
                else { $line->[1] = "var$obj->{VARS}{$arg}[0]"; }
            }
            
            # String argument
            else
            { 
                if(not exists $obj->{TEXTUAL}{$arg})
                {
                    $t++; $line->[1] = "msg$t";
                    $obj->{TEXTUAL}{$arg} = 
                        [ $t, "Stackable_ptr msg$t { new stk::Text { \"$arg\" } };" ];
                }
                else { $line->[1] = "msg$obj->{TEXTUAL}{$arg}[0]"; }
            }
        }
    }

    # Checks maximum argument size (items)
    for my $var(keys %{$obj->{ITEM}})
    {
        next unless($obj->{ITEM}{$var}); 
        # Ignores items that did not appear
        
        if(length($var) > $obj->{MAX_ARG}) 
        { $obj->{MAX_ARG} = length $var; }
    }                

    # Checks maximum argument size (attack)
    # The +3 comes from the 'x' in front of 
    # the name of the attack
    for my $var (keys %{$obj->{ATTACK}}) 
    { 
        if(length($var)+1 > $obj->{MAX_ARG}) 
        { $obj->{MAX_ARG} = length($var)+1; }
    }

    # Checks maximum argument size (others)
    # The +3 comes from the var name
    for my $var ($t, $n, $a, $v)
    {
        if(length($var)+3 > $obj->{MAX_ARG})
        { $obj->{MAX_ARG} = length($var)+3; }
    }
}
