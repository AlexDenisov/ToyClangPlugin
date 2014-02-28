## ToyClangPlugin

Simple clang plugin

### Installation

Build `llvm`/`clang` from sources
```bash
cd /opt
sudo mkdir llvm
sudo chown `whoami` llvm
cd llvm
export LLVM_HOME=`pwd`

git clone -b release_33 https://github.com/llvm-mirror/llvm.git llvm
git clone -b release_33 https://github.com/llvm-mirror/clang.git llvm/tools/clang
git clone -b release_33 https://github.com/llvm-mirror/clang-tools-extra.git llvm/tools/clang/tools/extra
git clone -b release_33 https://github.com/llvm-mirror/compiler-rt.git llvm/projects/compiler-rt

mkdir llvm_build
cd llvm_build
cmake ../llvm -DCMAKE_BUILD_TYPE:STRING=Release
make -j`sysctl -n hw.logicalcpu`
```

Get the plugin copy
```bash
cd $LLVM_HOME
git clone https://github.com/AlexDenisov/ToyClangPlugin.git
```

Build the plugin
```bash
mkdir build; cd build
cmake -G Xcode ..
open ToyClangPlugin.xcodeproj
```

Download [this](https://github.com/AlexDenisov/ToyClangPlugin/releases/download/0.0.1/XcodeHacking.zip) archive, unzip and run following commands

```bash
sudo mv HackedClang.xcplugin `xcode-select -print-path`/../PlugIns/Xcode3Core.ideplugin/Contents/SharedSupport/Developer/Library/Xcode/Plug-ins
sudo mv HackedBuildSystem.xcspec `xcode-select -print-path`/Platforms/iPhoneSimulator.platform/Developer/Library/Xcode/Specifications
```

Open your project and pudate build settings:

1. Select custom compiler

2. Disable modules

3. Add `OTHER_CFLAGS`

```
-Xclang -load -Xclang /opt/llvm/toy_clang_plugin/build/lib/Debug/ToyClangPlugin.dylib -Xclang -add-plugin -Xclang ToyClangPlugin
```

Build and run

