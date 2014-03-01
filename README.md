## ToyClangPlugin

Simple clang plugin. More details [here](http://l.rw.rw/clang_plugin)

This plugin shows you a warning in case of class' name starts with lowercse letter and shows an error in case when class' name contains underscore (`_`).

As a bonus it proposes you a FixIt hints

![Warning FixItHint](https://raw.github.com/AlexDenisov/ToyClangPlugin/master/screenshots/warning_fixit_hint.png)
![Error FixItHint](https://raw.github.com/AlexDenisov/ToyClangPlugin/master/screenshots/error_fixit_hint.png)

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
cd ToyClangPlugin
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

![Custom compiler](https://raw.github.com/AlexDenisov/ToyClangPlugin/master/screenshots/custom_compiler.png)

2. Disable modules

![Disable modules](https://raw.github.com/AlexDenisov/ToyClangPlugin/master/screenshots/disable_modules.png)

3. Add `OTHER_CFLAGS`

```
-Xclang -load -Xclang /opt/llvm/toy_clang_plugin/build/lib/Debug/ToyClangPlugin.dylib -Xclang -add-plugin -Xclang ToyClangPlugin
```

![Other C flags](https://raw.github.com/AlexDenisov/ToyClangPlugin/master/screenshots/other_cflags.png)

That's it. Build and run you project.
