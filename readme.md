# What

Example of how to compile a library (.so, .dylib, .dll) and load it into a running executable.
Also, a bash script to recompile & signal a reload on save.

# How

## 1) Recompile oF

Recompile your oF so that it creates a shared library with position-independent code.

change `line 241` in `./libs/openFrameworksCompiled/project/makefileCommon/compile.core.mk` from

```make
        $(CXX) $(OPTIMIZATION_CFLAGS) $(CFLAGS) $(CXXFLAGS) -MMD -MP -MF $(OF_CORE_OBJ_OUTPUT_PA    TH)$*.d -MT$(OF_CORE_OBJ_OUTPUT_PATH)$*.o -o $@ -c $<
```

to

```make
        $(CXX) -fPIC $(OPTIMIZATION_CFLAGS) $(CFLAGS) $(CXXFLAGS) -MMD -MP -MF $(OF_CORE_OBJ_OUTPUT_PA    TH)$*.d -MT$(OF_CORE_OBJ_OUTPUT_PATH)$*.o -o $@ -c $<
```
(or just use the patch:)

```sh
cp 0001-add-fPIC-flag-to-compile.core.mk.patch ../../../
git apply 0001-add-fPIC-flag-to-compile.core.mk.patch
```

then **recompile oF** - this is important!

```sh
cd libs/openFrameworksCompiles/project
make clean
SHAREDCORE=1 make
```

## 2) Fun times

```sh
# terminal 1:
# compile and run
make && make run

# terminal 2:
# start watchdog compilation
cd bin/data
./watchdog.sh

# terminal 3:
# livecoding!!! (save to update)
vi classy.cpp
```

# Env / Deps

- Ubuntu 15.04
- openFrameworks 0.9.4 (commit 374eaa0f7dbdc7e65a7618fa2564b8875473cf39)
- g++ (Ubuntu 4.9.2-10ubuntu13) 4.9.2