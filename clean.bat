@echo off

rm -rf *.sln Makefile *.make build/** */*.vcxproj */*.vcxproj.* Debug-windows-x86_64/** */bin/** */obj/**
rmdir -rf build Debug-windows-x86_64