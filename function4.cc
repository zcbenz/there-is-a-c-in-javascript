#include <v8.h>
#include <iostream>
#include <string>

using namespace v8;
using namespace std;

Handle<Value> girl (const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 1 && !args[0]->IsString ())
        return ThrowException(v8::String::New("Unexpected arguments"));

    args.This()->Set (String::New ("name"), args[0]);

    return Undefined ();
}

int main(int argc, char *argv[])
{
    HandleScope handle_scope;
    Handle<Context> context = Context::New();
    Context::Scope context_scope(context);

    Local<FunctionTemplate> func_tpl = FunctionTemplate::New (girl);

    Handle<Value> args[1] = { String::New ("Alice") };
    Handle<Object> alice = func_tpl->GetFunction()->NewInstance (1, args);
    alice->Set (String::New ("age"), Integer::New (21));

    cout << *String::AsciiValue (alice->Get(String::New("name")));

    return 0;
}
