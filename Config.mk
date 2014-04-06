# Project setting 
PROJECT := Robot-Battle
VERSION := 1.0

# Program settings
BIN     := Main rpc
ARLIB   := 
SHRLIB  := 

# Parser and Scanner
CXXLEXER  := Scanner.ll
CXXPARSER := Parser.yy

# Package info
MAINTEINER_NAME := Renato Cordeiro Ferreira
MAINTEINER_MAIL := renato.cferreira@hotmail.com
PRIORITY        := optional
SYNOPSIS        := Program for fighting!
DESCRIPTION     := Fight with robots to destroy the enemy base!

# Debian package
DEB_VERSION     := 1
DEB_PROJECT     := robot-battle
