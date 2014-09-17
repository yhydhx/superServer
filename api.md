### 目录
  * [购物车](#加入购物车)


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