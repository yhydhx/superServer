### 目录
  * [后台地址](#address)
  * [店铺主页](#store)
  * [购物车](#shopcar)
  * [商品详情](#product)
  * [类别商品](#category)
  * [搜索](#search)

###Address
  http://shop-api.herokuapp.com

###Shopcar
#### 1.加入购物车
选定规格，确定商品数量。

    Post /cars
    
**Input**

| Name      |     Type |   Description   |
| :-------- | --------:| :------: |
| product_id    |   number | 产品的ID  |
| value1    |   string |  规格一的属性值  |
| value2    |   string |  规格二的属性值  |
| quantity    |   number |  加入购物车的商品数量  |


#### 2.显示购物车

    Get /showcar
    
**Parameters**

    no
    
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

| Name     |     Type |   Description   |
| :-------- | --------:| :------: |
| quantity    |   number |  修改后的商品数量  |

**Response**

修改成功
```
Status: 200 OK
```
修改失败
```
Status: 403  forbidden
```
```json
{
  "id": "forbidden",
  "message": "Please modify your car!"
}
```

#### 4.删除购物车的商品
只能删除自己购物车的商品

    Delele /Cars/:id

**Response**

删除成功

    Status: 200 OK
    
删除失败    
```
Status: 403  forbidden
```
```json
{
  "id": "forbidden",
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
| name    |   string |  中文可能需要用js进行处理,待测试  |

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
