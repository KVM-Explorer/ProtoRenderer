# Proto Renderer

This is a prototype render system for different types of features.

# Architecture


# Features

## Graphics Features

- [ ] Culling
  - [ ] Frustum Culling
  - [ ] Occlusion Culling
  - [ ] Hi-Z Culling
  - [ ] GPU Culling
- [ ] Lighting
  - [ ] Directional Light
  - [ ] Point Light
  - [ ] Spot Light
- [ ] Light Culling
  - [ ] NDC Culling
  - [ ] Cluster Culling
  - [ ] Cone Test Culling
- [ ] Material
  - [ ] PBR
  - [ ] Physically Based Material
  - [ ] Material Graph
- [ ] Physically Based Rendering
- [ ] Shadow Mapping
  - [ ] PCF
  - [ ] PCSS
  - [ ] VSSM
  - [ ] CSM
- [ ] Screen Space Reflections
- [ ] Post Processing
- [ ] HDR
- [ ] Bloom
- [ ] TAA
- [ ] Motion Blur
- [ ] SSAO
- [ ] Depth of Field
- [ ] GI
  - [ ] SSAO
  - [ ] SSR
  - [ ] Light Probe
  - [ ] Baking
  - [ ] IBL
  - [ ] V
- [ ] IOT
- [ ] Atmospheric Scattering
- [ ] Volumetric Lighting
- [ ] Volumetric Fog
- [ ] Volumetric Clouds
- [ ] Auto Exposure

## Architecture Features

- [ ] RenderGraph
- [ ] Resource Alloc&Alias
- [ ] Resource LifeCycle
- [ ] UI System
- [ ] ECS
- [ ] Scene Graph


# TODO
* 系统结构

  * RenderGraph
  * Bindless
  * RHI
  * Resource Alloc&Alias
  * 反射
  * UI系统
  * Console Output
  * Log
  * Timeline
  * World/场景管理器
  * 资产管理
  * RenderGraph中间结果可视化
* ShadowMap

  * 软阴影
  * CSM
* 物理光照

  * 大气渲染
  * 体积雾
* 剔除

  * 光源剔除
  * GPU Driven Culling
  * Software Raster
* Render Path

  * GPU Driven Pipeline
* V-Buffer的管线
* 着色

  * 不透明
  * 半透明
  * 特殊材质着色
  * PBR光照
  * IOT实现
* GI

  * SSAO
  * IBL
  * SSR
  * VXGI
* 后期处理

  * Bloom
  * SSAO
* 物理相机

  * 自动曝光
  * 景深
* 抗锯齿效果

  * MSAA
  * TAA