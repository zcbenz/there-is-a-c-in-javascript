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
    context->Global()->Set (String::NewSymbol ("print"), 
                            func_tpl->GetFunction ());

    // Call in javascript
    Local<String> source = String::New ("print ('I', 'Love', 'C++', '!');");
    Script::Compile(source)->Run ();

    return 0;
}
