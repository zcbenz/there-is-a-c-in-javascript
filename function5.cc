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
    Local<FunctionTemplate> func_tpl = FunctionTemplate::New ();
    Local<ObjectTemplate> prototype = func_tpl->PrototypeTemplate ();
    prototype->Set (String::New ("proto_const"), Integer::New (2));
    prototype->Set (String::New ("proto_method"), FunctionTemplate::New (print));

    return 0;
}
