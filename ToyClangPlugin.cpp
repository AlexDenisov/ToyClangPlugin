#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"

using namespace clang;

namespace
{
    
    class ToyConsumer : public ASTConsumer
    {
    };

    class ToyASTAction : public PluginASTAction
    {
    public:
        virtual clang::ASTConsumer *CreateASTConsumer(CompilerInstance &Compiler,
                                                      llvm::StringRef InFile)
        {
            return new ToyConsumer;
        }

        bool ParseArgs(const CompilerInstance &CI, const
                       std::vector<std::string>& args) {
            return true;
        }
    };
}

static clang::FrontendPluginRegistry::Add<ToyASTAction>
X("ToyClangPlugin", "Toy Clang Plugin");

