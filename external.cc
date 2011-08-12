#include <v8.h>
#include <iostream>
#include <string>

using namespace v8;
using namespace std;

int main(int argc, char *argv[])
{
    HandleScope handle_scope;
    Handle<Context> context = Context::New();
    Context::Scope context_scope(context);

    std::string str ("Hello World!");
    Local<External> external = External::New (&str);
    cout << *static_cast<std::string*> (external->Value());

    return 0;
}
