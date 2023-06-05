### 单片机使用JSON序列化及反序列化使用指南



###### 构建：普通的JSON键值对

```c
    "age": 20,
    "score": 78.4,
    "name": "whik1194",
    "blog": "https://blog.csdn.net/whik1194",
    "wechat": "mcu149"
}

//构建函数
#include "jansson.h"

uint8_t Jansson1_Demo(void)
{
    json_t *root;
    json_t *blog_string;
    char *str;
    
    root = json_object();

    json_object_set_new(root, "status", json_boolean(JSON_TRUE));
    json_object_set_new(root, "age", json_integer(20));
    json_object_set_new(root, "score", json_real(78.4));
    json_object_set_new(root, "name", json_string("whik1194"));
    
    blog_string = json_string("https://blog.csdn.net/whik1194");
    json_object_set_new(root, "blog", blog_string);
    
    json_object_set_new(root, "wechat", json_string("mcu149"));
    
    str = json_dumps(root, JSON_PRESERVE_ORDER);
    
    json_decref(root);
   
    LOG1("\r\njson_string:\r\n%s\r\n", str);
    return 0;
}
```



 ###### 构建：套JSON对象

 ```C
  {
      "success": "1",
      "result": {
          "timestamp": "1592640249",
          "datetime_1": "2020-06-20 16:04:09",
          "week_1": 6,
          "week_2": "Saturday"
      }
  }
  
  
  //构建函数
  uint8_t Jansson2_Demo(void)
  {
      json_t *root;
      json_t *result_obj;
      char *str;
  
      root = json_object();
      result_obj = json_object();
  
      json_object_set_new(result_obj, "timestamp", json_string("1592640249"));
      json_object_set_new(result_obj, "datetime_1", json_string("2020-06-20 16:04:09"));
      json_object_set_new(result_obj, "week_1", json_integer(1));
      json_object_set_new(result_obj, "week_2", json_string("Saturday"));
      
      json_object_set_new(root, "success", json_string("1"));
      json_object_set_new(root, "result", result_obj);
      
      str = json_dumps(root, JSON_PRESERVE_ORDER);
      json_decref(root);
  
      LOG1("\r\njson_string:\r\n%s\r\n", str);
      return 0;
  }
 ```



###### 构建：包含数组的JSON对象

```C
{
    "location": [{
        "name": "Faye",
        "address": "Beijing"
    }, {
        "name": "Andy",
        "address": "ShangHai"
    }, {
        "name": "Lisa",
        "address": "ShenZhen"
    }],
    "time": "2018-11-17"
}


//构建函数
uint8_t Jansson3_Demo(void)
{
    json_t *root;
    json_t *array_obj;
    char *str;
    
    char name[3][20] = {"Faye", "Andy", "Lisa"};
    char address[3][20] = {"Beijing", "ShangHai", "ShenZhen"};
    uint8_t idx = 0;
    json_t *array_value;
    
    root = json_object();
    
    array_obj = json_array();
    array_value = json_object();
    
    for(idx = 0; idx < 3; idx++)
    {
        json_object_set_new(array_value, name[idx], json_string(address[idx]));
        json_array_insert_new(array_obj, idx, array_value);
//        json_array_append_new(array_obj, array_value);
    }
        
    json_object_set_new(root, "location", array_obj);       //location键的值是一个数组
    json_object_set_new(root, "time", json_string("2018-11-17"));
    
    str = json_dumps(root, JSON_PRESERVE_ORDER);
    json_decref(root);

    LOG1("\r\njson_string:\r\n%s\r\n", str);
    return 0;
}

```



###### 解析：JSON字符串，包括字符串、整形和布尔类型三种类型的键值对

```C
//JSON字符串，包括字符串、整形和布尔类型三种类型的键值对：
{
    "status": true,
    "age": 20,
    "name": "whik1194",
    "blog": "https://blog.csdn.net/whik1194",
    "wechat": "mcu149"
}

//解析函数      
uint8_t Jansson1_Demo(void)
{
    const char *text = "{\"status\":true,\"age\":20,\"score\":78.4,\"name\":\"whik1194\",\"blog\":\"https://blog.csdn.net/whik1194\",\"wechat\":\"mcu149\"}";
    
    json_error_t error;
    json_t *root;
    json_t *status;
    
    char *name, *blog, *wechat;
    int age;
    double score;
    
    root = json_loads((const char*)text, 0, &error); 
    if(json_is_object(root))
    {
        LOG1("root format correct\r\n");
        
        /* string 类型的解析 */
        name = (char *)json_string_value(json_object_get(root, "name"));
        blog = (char *)json_string_value(json_object_get(root, "blog"));
        wechat = (char *)json_string_value(json_object_get(root, "wechat"));
        
        LOG1("name: %s\r\n", name);
        LOG1("blog: %s\r\n", blog);
        LOG1("wechat: %s\r\n", wechat);
        
        /* int 类型的解析 */
        age = json_integer_value(json_object_get(root, "age"));
        LOG1("age: %d\r\n", age);
        
        /* double 类型的解析 */
        score = json_real_value(json_object_get(root, "score"));
        LOG1("score: %.1f\r\n", score);
        
        /* bool 类型的解析 */
        status = json_object_get(root, "status");
        if(json_is_true(status))
            LOG1("status: true\r\n");
        else if(json_is_false(status))
            LOG1("status: false\r\n");
    }
    else
    {
        printf("root format error:%d-%s\r\n", error.line, error.text);
        return 1;
    }
    return 0;
}   
```



###### 解析：键的值是一个对象:JSON字符串，其中result键的值是一个JSON对象，包括几组键值对：

```c
{
    "success": "1",
    "result": {
        "timestamp": "1592640249",
        "datetime_1": "2020-06-20 16:04:09",
        "week_1": "6",
        "week_2": "Saturday"
    }
}

//解析函数
uint8_t Jansson2_Demo(void)
{
    const char *text = "{\"success\":\"1\",\"result\":{\"timestamp\":\"1592640249\",\"datetime_1\":\"2020-06-20 16:04:09\",\"week_1\":\"6\",\"week_2\":\"Saturday\"}}";
    json_error_t error;
    json_t *root;
    json_t *result;
    
    char *success;
    char *timestamp;
    char *datetime_1;
    char *week_1;

    root = json_loads((const char*)text, 0, &error); 
    if(json_is_object(root))
    {
        LOG1("root format correct\r\n");
        success = (char *)json_string_value(json_object_get(root, "success"));
        LOG1("success:%s\r\n", success);
        
        result = json_object_get(root, "result");
        if(json_is_object(result))
        {
            timestamp = (char *)json_string_value(json_object_get(result, "timestamp"));
            datetime_1 = (char *)json_string_value(json_object_get(result, "datetime_1"));
            week_1 = (char *)json_string_value(json_object_get(result, "week_1"));
            
            LOG1("timestamp:%s\r\n", timestamp);
            LOG1("datetime_1:%s\r\n", datetime_1);
            LOG1("week_1:%s\r\n", week_1);
        }
        else 
        {
            LOG1("reuslt format error\r\n");
            return 1;
        }
    }
    else
    {
        LOG1("root format error:%d-%s\r\n", error.line, error.text);
        return 1;
    }
    return 0;
}
```



###### 解析：键的值是一个数组

```c
{
    "location": [{
        "name": "Faye",
        "address": "Beijing"
    }, {
        "name": "Andy",
        "address": "ShangHai"
    }, {
        "name": "Lisa",
        "address": "ShenZhen"
    }],
    "time": "2018-11-17"
}

//解析函数
uint8_t Jansson3_Demo(void)
{
    const char *text = "{\"location\":[{\"name\":\"Faye\",\"address\":\"Beijing\"},{\"name\":\"Andy\",\"address\":\"ShangHai\"},{\"name\":\"Lisa\",\"address\":\"ShenZhen\"}],\"time\":\"2018-11-17\"}";
   
    json_error_t error;
    json_t *root;
    json_t *location_arr;
    json_t *location;
    
    char *name, *address;
    char *time;
    int idx;
    
    root = json_loads((const char*)text, 0, &error); 
    if(json_is_object(root))
    {
        LOG1("root format correct\r\n");
        time = (char *)json_string_value(json_object_get(root, "time"));
        location_arr = json_object_get(root, "location");
        if(json_is_array(location_arr))
        {
            for(idx = 0; idx < json_array_size(location_arr); idx++)
            {
                location = json_array_get(location_arr, idx);
                name = (char *)json_string_value(json_object_get(location, "name"));
                address = (char *)json_string_value(json_object_get(location, "address"));
                LOG1("%d: %s-%s\r\n", idx, name, address);
            }
        }
    }
    else
    {
        LOG1("root format error:%d-%s\r\n", error.line, error.text);
        return 1;
    }
    return 0;
}
```



### 注意事项：

1. 如果出现解析失败，或者解析错误，可以尝试增加Heap_Size大小：
2. 解析和生成json的时候要保证有足够的堆空间，如果堆大小不够会处理失败。博主一般设置3KB的heap。 x0C00

![](\images\heap.png)