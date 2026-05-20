### About

ECS is a entity component system library inspired by [EnTT](https://github.com/skypjack/entt), but not as fast and robust :)

#### Additional info
ECS is built to be a submodule for other projects. This project uses [Premake5](https://premake.github.io/download) for build configuration

### Installation as a submodule

1. Add as a submodule

```
git submodule add https://github.com/stapxd/ECS.git [path]
git submodule update --init
```

2. Add `ECS/include` folder into your project's additional include directories

3. Link your project with `ECS`

> As ECS uses premake5 it is much easier to do last 2 steps with premake

### Tips

In `Example/` folder you can find main.cpp with example usage of the library which you can copy to test yourself!

