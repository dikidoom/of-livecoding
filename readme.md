# What

Example of how to compile a library (.so, .dylib, .dll) and load it into a running executable.
Also, a bash script to recompile & signal a reload on save.

# How

```
# terminal 1:
# compile and run
make && make run

# terminal 2:
# start watchdog compilation
cd bin/data
./watchdog.sh

# terminal 3:
# livecoding!!! (save to update)
vi simple.cpp
```

# Env / Deps

- Ubuntu 15.04
- openFrameworks 0.9.4 (commit 374eaa0f7dbdc7e65a7618fa2564b8875473cf39)
- g++ (Ubuntu 4.9.2-10ubuntu13) 4.9.2