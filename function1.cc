#include <v8.h>
#include <iostream>
#include <string>

using namespace v8;
using namespace std;

Handle<Value> print (const Arguments& args) {
    HandleScope scope;

    for (int i = 0; i< args.Length(); ++i) {
        cout << *String::Utf8Value (args[i]) << " ";
    }

    cout << endl;

    return Undefined ();
}

int main(int argc, char *argv[])
{
    HandleScope handle_scope;
    Handle<Context> context = Context::New();
    Context::Scope context_scope(context);

    // Generate Function
    Local<FunctionTemplate> func_tpl = FunctionTemplate::New (print);
    func_tpl->SetClassName (String::NewSymbol ("print"));
    Local<Function> func = func_tpl->GetFunction ();
    cout << *String::Utf8Value (func) << endl;

    // Generate parameters
    Local<Value> args[4] = {
        String::New ("I"),
        String::New ("Love"),
        String::New ("C++"),
        String::New ("!")
    };

    // Call Function
    func->Call (Object::New (), 4, args);

    return 0;
}
