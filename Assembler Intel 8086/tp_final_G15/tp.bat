@echo off
tasm catch
tlink /t catch
catch
tasm maintpf
tasm val
tlink maintpf val
maintpf
@echo "Listo"