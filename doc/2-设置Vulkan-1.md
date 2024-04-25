# Vulkan工作模型简介

Vulkan是一个协议规范,这就意味着它规定了什么是调用API的程序(即用户或者程序员)负责的,什么是驱动和硬件负责的.

Vulkan对用户暴露一个或者多个实例(Instance),每个实例可以拥有一个或者多个物理设备(physical device),在此基础上设置一个或者多个逻辑设备(logical device)进行工作,如果多个物理设备拥有相似的性质,则会被放入同一个设备组中创建为一个逻辑设备(比如四路4090交火).

Vulkan中的物理设备拥有许多队列(queue),所有队列工作都是异步的,这些队列被分为几个队列族(queue family),相同队列族中的队列提供提供相互的兼容性,不同族之间的队列**不**保证兼容.每个队列族用于承担不同的任务,比如浮点计算,图形变换,视频编码/解码等.

Vulkan中所有的命令(command)都会先被存储到命令缓冲区(command buffer)中,然后提交(submit)给队列执行,同一个队列内部的命令保持顺序执行,不同队列之间的同步需要程序员显式插入栅栏(fence)或者信号量(semaphore).命令缓冲区来自命令缓冲池(command buffer pool)的手动分配.

Vulkan协议满足C99标准且支持多线程,一些数据需要显式的外部同步,具体可参考Vulkan标准.

# Vulkan 中的层与扩展

Vulkan是拥有层(layer)与扩展(extension)的概念的.Vulkan中最重要的层就是验证层(Validation Layer),启用验证层可以帮助你快速揪出错误,因为Vulkan为了性能在出错时只会返回一个错误码,程序不会抛出异常,也不会崩溃(除非致命错误).

Vulkan本身只负责使用GPU,处理图形数据,而不负责将画面输出到屏幕上,因此将画面数据到屏幕上需要额外的扩展,在Vulkan中所有扩展都带有KHR字样,而硬件厂商(vendor)提供的跟自身GPU有关的特色(feature)则会带有厂商相关的字眼(比如NV字样).

# 包含Vulkan头文件

包含 vulkan/core.h 即可.

# 设置 instance

instance可以理解为vulkan应用程序的代表,设置Vulkan首先需要从设置instance开始.

为了设置instance,就需要VkCreateInstance()函数,Vulkan中所有创建某个Vulkan对象(比如实例,设备,队列,命令,着色器等)的命令都有 vkCreate 前缀,Vulkan中所有通过分配内存创建对象的命令都有 vkAllocate 前缀.

所有具有 vkCreate 前缀的函数都需要 Vk\*\*\*CreateInfo 形式名称的结构体作为参数,所有具有 vkAllocate 前缀的函数都需要 Vk\*\*\*AllocateInfo 形式名称的结构体作为参数.

## 查询系统相关特性

在创建instance之前,我们需要查询自己的电脑上支持什么层和扩展.

使用 vkGet\*\*\* 和 vkEnumerate\*\*\* 可以查询系统中支持的特性,而API版本,层和扩展需要使用的函数为

```c
vkEnumerateInstanceVersion()
vkEnumerateInstanceLayerProperties()
vkEnumerateInstanceExtensionProperties()
vkEnumerateDeviceExtensionProperties()
```
第一个函数查询VulkanAPI版本,第二个函数查询instance层面有哪些层支持,第三个函数查询instance层面有哪些扩展支持,第四个函数查询设备层面有哪些扩展支持.

以`vkEnumerateInstanceLayerProperties()`函数为例子,它接收一个`uint32_t* pPropertyCount`和`VkLayerProperties* pProperties` 两个参数.

这个函数在 pProperties 为 nullptr 时,pPropertyCount 会返回系统支持的层的数量,而它不为 nullptr 时,函数会通过这个指针返回一个`VkLayerProperties`数组,这个数组存储了所有层的特性.

示例如下:

```c++
uint32_t layerCount=0;
std::vector<VkLayerProperties> avaiableLayers;
vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
availableLayers.resize(layerCount);
vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());    
```

## 设置函数参数

按照规范中的说明设置 VkInstanceCreateInfo 和 VkApplicationCreateInfo 即可.
