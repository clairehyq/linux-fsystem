# Studio 16-21 and Lab5

## Group Members

| Group Member | WUSTL ID  | Github ID    |
| ------------ | --------- | ------------ |
| Claire Huo   | huoyuqian | clairehyq    |
| York Liu     | yorkliu   | l0exy1h      |
| Yuqi Lei     | leiy      | ximenshaoxia |

## Folder structure

- `lab5/`: a complete implementation of the lab5 shell
- `lab5-tests/`: all tests on piazza
- `Studio16-21/`: all studios and tests
- `targets/`: this will appear after make. **All executables will be here**.
- `unit-test-lib/`: York's unit test library
- `config.mk`: this will be sourced by all Makefiles in the subdirectories. Executable name and CXXFLAGS are defined here.
- `Makefile`: the top-level makefile. Users should be interacting with this Makefile only.
- `README.md`: this file
  - There are Readme files in `lab5` and `studio` folders. They contain answers to the questions in the lab specification

## How to make and test

- To make everything, cd into the directory that contains this readme and

  ```shell
  make
  ```

  - the default compiler is `g++`
  - to use a different compiler (for example, `clang++`)

  ```shell
  env CXX=clang++ make
  ```

- The above command will put all executables in `targets/`

  - The lab5 shell is `targets/lab5`
  - **The tests on piazza will be in one executable: `targets/test-piazza-lab5`**
  - The Studio16, for example, will be `targets/studio16`
  - The Tests for studio 15, for example, will be `targets/test-studio16`
  - There will also be `liblab5.a`: a static library containing all implementation of lab5 excluding the main() function. This can be used to write more tests. In fact, all studio tests are made this way. 

- To compile only the tests for lab5

  ```shell
  make -C lab5
  make -C lab5-tests
  ```
