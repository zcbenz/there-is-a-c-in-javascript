#include <v8.h>
#include <iostream>
#include <string>

using namespace v8;
using namespace std;

class Point {
    public:
        Point (int x, int y)
            :x (x), y (y)
        {
        }

        int x, y;
};

Handle<Value> XGetter (Local<String> property, const AccessorInfo& info) {
    Handle<Object> obj = info.This ();
    Point& point = *static_cast<Point*> (
            Local<External>::Cast(obj->GetInternalField(0))->Value ());

    return Integer::New (point.x);
}
 
void XSetter (Local<String> property, Local<Value> value,
              const AccessorInfo& info) {
    Handle<Object> obj = info.This ();
    Point& point = *static_cast<Point*> (
            Local<External>::Cast(obj->GetInternalField(0))->Value ());

    point.x = value->Int32Value();
}

Handle<Value> YGetter (Local<String> property, const AccessorInfo& info) {
    Handle<Object> obj = info.This ();
    Point& point = *static_cast<Point*> (
            Local<External>::Cast(obj->GetInternalField(0))->Value ());

    return Integer::New (point.y);
}
 
void YSetter (Local<String> property, Local<Value> value,
              const AccessorInfo& info) {
    Handle<Object> obj = info.This ();
    Point& point = *static_cast<Point*> (
            Local<External>::Cast(obj->GetInternalField(0))->Value ());

    point.y = value->Int32Value();
}

int main(int argc, char *argv[])
{
    HandleScope handle_scope;
    Handle<Context> context = Context::New();
    Context::Scope context_scope(context);

    // 建造ObjectTemplate
    Handle<ObjectTemplate> obj_tpl = ObjectTemplate::New ();
    obj_tpl->SetInternalFieldCount (1);
    obj_tpl->SetAccessor(String::New("x"), XGetter, XSetter);
    obj_tpl->SetAccessor(String::New("y"), YGetter, YSetter);

    // 建立Object，并与C++对象绑定
    Point point (10, 10);
    Handle<Object> obj = obj_tpl->NewInstance ();
    obj->SetInternalField (0, External::New (&point));

    // 打印结果
    cout << *String::AsciiValue (obj->Get (String::New ("x"))) << endl;
    cout << *String::AsciiValue (obj->Get (String::New ("y"))) << endl;

    return 0;
}
