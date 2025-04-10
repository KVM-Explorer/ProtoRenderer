# TODO

- [ ] 调整后端架构的宏控制方式，现在需要将宏泄漏到Client APP中，期望能够通过单独在Engine定义宏直接控制，现阶段主要原因是宏在Include下泄露到Client App。

# Record 

1. 使用DirectX-Headers后，应该避免和原始的d3d12.h混合使用否则容易因为依赖触发编译错误，找不到定义（可能时存在循环引用）。 若要使用应该直接使用DirectX-Headers替代原始的d3d12.h
2. 参考坐标系采用DirectX的坐标系，即X+为右，Y+为上，Z+为前。 


# RoadMap

Step1. 完善资源绑定和渲染流程
1. 优化Command和Pool的组织回收方式
2. 完善Mesh Container的上传流程
3. 将部分职责转移到Engine中，而不是App Client
4. 基于RenderGraph创建Image/Texture
6. 导入原始无材质白模
5. 解决资源申请和析构泄露的问题
7. 基于架构在Design中给出详细设计层级
8. 完善InputElement数据的组织形式(参考Maxwell)

Step2. GPU Driven Pipeline DrawCall



Step2.1 ECS 
1. 优化ECS架构，将ECS和RenderGraph分离，ECS应该只负责数据组织，RenderGraph负责数据组织和渲染流程。
2. 对于ECS的性能效率进行优化和测试


Step3. 面向PBR光照系统/Render Features

1. 设计完善Material模块，同时导入资产数据
2. 实现光照、阴影Feature
