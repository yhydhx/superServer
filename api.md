### 目录
#### 前端
  * [后台地址](#address)
  * [店铺主页](#store)
  * [购物车](#shopcar)
  * [商品详情](#product)
  * [类别商品](#category)
  * [搜索](#search)
  * [用户](#user)

####后端
  * [后台登录](#signin)
  * [商品操作](#operation)
  * [修改店铺信息](#storeinformation)
  * [分类操作](#operate categories)

###Address
  http://shop-api.herokuapp.com

###Shopcar
#### 1.加入购物车
选定规格，确定商品数量。

    Post /cars
    
**Input**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| nosign_id    |  string | 没有登录的标记id,nosign_id与remember_token需要一个   |
| remember_token    |   string | 登录之后获得的token,nosign_id与remember_token需要一个   |
| product_id    |   number | 产品的ID  |
| value1    |   string |  规格一的属性值  |
| value2    |   string |  规格二的属性值  |
| quantity    |   number |  加入购物车的商品数量  |

**Response**
```json
{"code":"success"}
```


#### 2.显示购物车

    Get /cars
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| nosign_id    |  string | 没有登录的标记id,nosign_id与remember_token需要一个   |
| remember_token    |   string | 登录之后获得的token,nosign_id与remember_token需要一个   |


    
**Response**
```
HTTP/1.1 200 OK 
```
```json
    [
  {
    "id": 1,
    "product_id": 8,
    "name": "车1",
    "picture_url": "/assets/s1.jpg",
    "quantity": 1,
    "skucate": {
      "skucate_id": 2,
      "price": 3000.0,
      "oldprice": 4000.0,
      "value1": "红色",
      "value2": "M22"
    }
  },
  {
    "id": 2,
    "product_id": 8,
    "name": "车1",
    "picture_url": "/assets/s1.jpg",
    "quantity": 2,
    "skucate": {
      "skucate_id": 2,
      "price": 3000.0,
      "oldprice": 4000.0,
      "value1": "红色",
      "value2": "M22"
    }
  }
]
```

#### 3.修改购物车商品数量
只能修改自己购物车的商品
```
Put /Cars/:id
```
**Input**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| nosign_id    |  string | 没有登录的标记id,nosign_id与remember_token需要一个   |
| remember_token    |   string | 登录之后获得的token,nosign_id与remember_token需要一个   |
| quantity    |   number |  修改后的商品数量  |

**Response**

修改成功

    Status: 200 OK

```json
{"code":"success"}
```
修改失败
```
Status: 403  forbidden
```
```json
{
  "id": "forbidden",
  "code":"success",
  "message": "Please modify your car!"
}
```

#### 4.删除购物车的商品
只能删除自己购物车的商品

    Delele /Cars/:id

**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| nosign_id    |  string | 没有登录的标记id,nosign_id与remember_token需要一个   |
| remember_token    |   string | 登录之后获得的token,nosign_id与remember_token需要一个   |

**Response**

删除成功

    Status: 200 OK
    
```json
{"code":"success"}
```
删除失败    
```
Status: 403  forbidden
```
```json
{
  "code":"failure",
  "message": "Please delete your car!"
}
```
### Product
#### 1.显示商品详情
会显示商品的名称，所有的规格详情，以及商品详细介绍等

    Get /products/:id
    
**Response**

    Status: 200 OK
    
```json
{
  "id": 8,
  "name": "车1",
  "category_id": 1,
  "imglist": [
    {
      "img": "s1.jpg",
      "main_img": true
    },
    {
      "img": "s2.jpg",
      "main_img": false
    }
  ],
  "property": [
    {
      "name": "品牌",
      "value": "奔驰"
    },
    {
      "name": "车重",
      "value": "2T"
    },
    {
      "name": "车轮",
      "value": "中国制造"
    }
  ],
  "detail": [
    {
      "text": "车身照",
      "img": "s5.jpg"
    },
    {
      "text": "车头照",
      "img": "s6.jpg"
    }
  ],
  "skucate": [
    {
      "name1": "颜色",
      "value1": "黄色",
      "name2": "车型",
      "value2": "M11",
      "price": 4000.0,
      "oldprice": 5000.0,
      "quantity": 50
    },
    {
      "name1": "颜色",
      "value1": "红色",
      "name2": "车型",
      "value2": "M22",
      "price": 3000.0,
      "oldprice": 4000.0,
      "quantity": 30
    }
  ]
}
```
### Catogory
#### 1.所属列别的商品
每次发送10个商品

    Get /Categories/:id
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| page    |   number |  每页10个 从1开始  |
**Response**

    Status: 200 OK

```json
[
  {
    "id": 8,
    "name": "车1",
    "category_id": 1,
    "picture_url": "/assets/s1.jpg",
    "price": 3000.0,
    "quantity": 80
  },
  {
    "id": 16,
    "name": "车2",
    "category_id": 1,
    "picture_url": "/assets/s3.jpg",
    "price": 4400.0,
    "quantity": 66
  }
]
```
### Search
#### 1.搜索
输入商品名称的开头,返回匹配到的商品名称及id

    Get /search
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| name    |   string |  查询内容  |

**Response**

e.g: name=车
```json
[
  {
    "id": 8,
    "name": "车1"
  },
  {
    "id": 9,
    "name": "车2"
  },
  {
    "id": 16,
    "name": "车2"
  },
  {
    "id": 10,
    "name": "车3"
  }
]
```
### Store
#### 店铺主页
会返回店铺的轮播图片，店铺信息，及种类信息

    Get /

**Response**

    Status 200 OK
    
```json
{
  "id": 1,
  "name": "专属",
  "background": "背景.jpg",
  "slogan": "这是一家小店铺的标语。",
  "carousel": [
    {
      "picture": "/assests/s1.jpg"
    },
    {
      "picture": "/assests/s3.jpg"
    },
    {
      "picture": "/assests/s4.jpg"
    },
    {
      "picture": "/assests/s5.jpg"
    }
  ],
  "category": [
    {
      "id": 1,
      "name": "水果",
      "product": [
        {
          "product_id": 8,
          "picture": "/assets/s1.jpg"
        },
        {
          "product_id": 16,
          "picture": "/assets/s3.jpg"
        }
      ]
    },
    {
      "id": 4,
      "name": "法拉利",
      "product": [
        {
          "product_id": 9,
          "picture": "/assets/s2.jpg"
        }
      ]
    },
    {
      "id": 5,
      "name": "奔驰",
      "product": [
        {
          "product_id": 10,
          "picture": "/assets/s3.jpg"
        },
        {
          "product_id": 11,
          "picture": "/assets/s4.jpg"
        }
      ]
    },
    {
      "id": 6,
      "name": "宝马",
      "product": [
        {
          "product_id": 14,
          "picture": "/assets/s7.jpg"
        }
      ]
    }
  ]
}
```
### User
#### 1.登录
传入email和密码，返回一个remember_token用于有权限的操作

    Post /signin

**Input**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| email    |   string |  用户邮箱  |
| password    |   string |  用户密码  |

**Response**
登录成功
```json
{
  "code": "success",
  "user_id": 1,
  "remember_token": "2vmqmULPTxyLZGGO3JGFZQ"
}
```
登录失败
```json
{"code":"failure"}
```

#### 2.注册
每项必填

    Post /users

**Input**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| email    |   string |  用户邮箱  |
| password    |   string |  用户密码  |
| password_confirmation    |   string |  密码确认  |
| name    |   string |  姓名  |
| province    |   string |  省份  |
| city    |   string |  城市  |
| address    |   string |  详细地址  |
| phone    |   number |  电话  |

**Response**
成功
```json
{
  "code": "success",
  "user_id": 3,
  "remember_token": "Cdvy8RKqExxDf0jsFfNkGw"
}
```
失败,返回错误
```json
{
  "code": "failure",
  "errors": {
    "email": [
      "has already been taken"
    ]
  }
}
```

#### 3.收藏or取消收藏
收藏店铺

    Get /users/:id/collect or /users/:id/uncollect
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |
| store_id    |   number |  店铺id  |

**Response**
```json
{"code":"success"}
```

#### 4.关注or取消关注
关注商品

    Get /users/:id/follow or /users/:id/unfollow
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |
| product_id    |   number |  商品id  |

**Response**
```json
{"code":"success"}
```


### 后端API

### Signin
#### 1.后台登录
传入email和密码，返回一个remember_token用于有权限的操作

    Post /admin/signin

**Input**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| email    |   string |  用户邮箱  |
| password    |   string |  用户密码  |

**Response**
登录成功
```json
{
  "code": "success",
  "owner_id": 1,
  "remember_token": "2vmqmULPTxyLZGGO3JGFZQ"
}
```
登录失败
```json
{"code":"failure"}
```

### Operation
#### 1.下架商品
将商品下架，并不是删除

    Get /admin/products/:id/drop_product
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |

**Response**
```json
{"code":"success"}
```
#### 2.将下架的商品上架
重新上架

    Get /admin/products/:id/pick_product
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |

**Response**
```json
{"code":"success"}
```
#### 3.查看下架的商品
列出所有下架的商品，属性包括商品名称，图片等

    Get /admin/products/show_down_products
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |

**Response**
```json
[
  {
    "id": 1,
    "name": "车-2",
    "category_id": 1,
    "picture_url": "/public/my/upload/directory/s1.jpg",
    "price": 10000.0,
    "quantity": 10
  },
  {
    "id": 2,
    "name": "车-2",
    "category_id": 1,
    "picture_url": "/public/my/upload/directory/s1.jpg",
    "price": 20000.0,
    "quantity": 20
  }
]
```
#### 4.查看上架的商品
分页列出所有上架的商品，属性包括商品名称，图片等

    Get /admin/products/show_up_products
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |
| page    |   number |  每页10个 从1开始  |

**Response**
```json
[
  {
    "id": 14,
    "name": "车-23",
    "category_id": 2,
    "picture_url": "/public/my/upload/directory/s2.jpg",
    "price": 30000.0,
    "quantity": 30
  },
  {
    "id": 17,
    "name": "车-26",
    "category_id": 2,
    "picture_url": "/public/my/upload/directory/s2.jpg",
    "price": 60000.0,
    "quantity": 60
  },
  {
    "id": 18,
    "name": "车-27",
    "category_id": 2,
    "picture_url": "/public/my/upload/directory/s2.jpg",
    "price": 70000.0,
    "quantity": 70
  },
 
  {
    "id": 22,
    "name": "车-31",
    "category_id": 2,
    "picture_url": "/public/my/upload/directory/s2.jpg",
    "price": 110000.0,
    "quantity": 110
  },
  {
    "id": 23,
    "name": "车-41",
    "category_id": 3,
    "picture_url": "/public/my/upload/directory/s3.jpg",
    "price": 10000.0,
    "quantity": 10
  },
  {
    "id": 24,
    "name": "车-42",
    "category_id": 3,
    "picture_url": "/public/my/upload/directory/s3.jpg",
    "price": 20000.0,
    "quantity": 20
  }
]
```
#### 5.删除下架的商品
删除商品的所有信息，包括各种规格

    Delete /admin/products/:id

**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |

**Response**
```json
{"code":"success"}
```

### Storeinformation
#### 1.修改店铺信息
修改店铺名称，标语，背景等

    Put /admin/stores/:id
  
 **Input** 
 
| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |
| name    |   string |   名称  |
| slogan    |   string |  标语  |
| background    |   string |  背景图片  |

**Response**
```json
{"code":"success"}
```
### Operate categories
#### 1.展示所有分类

    Get /admin/categories
    
**Parameters**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |

**Response**
```json
[
  {
    "id": 1,
    "name": "奔驰"
  },
  {
    "id": 2,
    "name": "法拉利"
  },
  {
    "id": 3,
    "name": "奥迪"
  }
]
```
#### 2.添加分类

    Post /admin/categories
    
**Input**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |
| name    |   string | 类别名称  |

**Response**
```json
{
  "code": "success",
  "category_id": 4
}
```
#### 3,修改分类名称

    Put /admin/categories/:id
  
 **Input** 
 
| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| remember_token    |   string |  登录之后获得的认证  |
| name    |   string |   名称  |

**Response**
```json
{"code":"success"}
```