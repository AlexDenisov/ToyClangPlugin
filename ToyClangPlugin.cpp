#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"

using namespace clang;

namespace
{
    
    class ToyClassVisitor : public RecursiveASTVisitor<ToyClassVisitor>
    {
    private:
        ASTContext *context;
    public:
        void setContext(ASTContext &context)
        {
            this->context = &context;
        }
        
        bool VisitObjCInterfaceDecl(ObjCInterfaceDecl *declaration)
        {
            checkForLowercasedName(declaration);
            return true;
        }
        
        void checkForLowercasedName(ObjCInterfaceDecl *declaration)
        {
            StringRef name = declaration->getName();
            char c = name[0];
            if (isLowercase(c)) {
                DiagnosticsEngine &diagEngine = context->getDiagnostics();
                unsigned diagID = diagEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Class name should not start with lowercase letter");
                SourceLocation location = declaration->getLocation();
                diagEngine.Report(location, diagID);
            }
        }
    };
    
    class ToyConsumer : public ASTConsumer
    {
    public:
        void HandleTranslationUnit(ASTContext &context) {
            visitor.setContext(context);
            visitor.TraverseDecl(context.getTranslationUnitDecl());
        }
    private:
        ToyClassVisitor visitor;
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

