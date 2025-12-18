# AboutWin

A Minimal C++ example application to show Windows version information.

## Building

Compiling is done with MinGW32 for portability and supporting legacy Windows versions.

I build all my Win32 C/C++ projects with [w64devkit](https://github.com/Alex313031/win32-devkit)
(actually, I use my [fork that supports Windows 2000](https://github.com/Alex313031/win32-devkit)),
and specifically, I use it with my GN/Ninja build system called [gn-legacy](https://github.com/Alex313031/gn-legacy).
GN/Ninja is unneeded, and one can also use MSYS2 MinGW32 (make sure it's not the UCRT or x64 versions).

To do a regular build from MSYS2 MinGW32 or w64devkit (x86 version):

```cmd
  make all -j4
```
