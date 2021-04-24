#include <Magick++.h>
#include <napi.h>

#include <list>

using namespace std;
using namespace Magick;

Napi::Value Jpeg(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  Napi::Object obj = info[0].As<Napi::Object>();
  string path = obj.Get("path").As<Napi::String>().Utf8Value();

  Blob blob;

  Image image;
  image.read(path);
  image.quality(1);
  image.magick("JPEG");
  image.write(&blob);

  Napi::Object result = Napi::Object::New(env);
  result.Set("data",
          Napi::Buffer<char>::Copy(env, (char *)blob.data(), blob.length()));
  result.Set("type", "jpg");
  return result;
}