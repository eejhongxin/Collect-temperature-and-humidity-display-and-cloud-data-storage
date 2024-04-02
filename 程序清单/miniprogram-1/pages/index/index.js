Page({
  data: {
   temp:0,
   humi:0
  },
  // 事件处理函数
  getinfo(){
    var that = this
    wx.request({
    url: "https://api.heclouds.com/devices/1051580320/datapoints",   
    //将请求行中的数字换成自己的设备ID
    header: {
      "api-key": "1ZXQyfKnqL1bqEV0D0JJqbL7pmc=" //自己的api-key
    },
    method: "GET",
    success: function (e) {
      console.log("获取成功",e)
      that.setData({
        temp:e.data.data.datastreams[0].datapoints[0].value,
        humi:e.data.data.datastreams[1].datapoints[0].value
      })
      console.log("temp==",that.data.temp)
    }
   });
  },

  kai:function(){
    let data={
    "datastreams": [  
	{"id": "ledbtn","datapoints":[{"value": 1}]},
	//led是数据流的名称，value是要传上去的数值
    	]	
  }
   //按钮发送命令控制硬件
    wx.request({
      url:'https://api.heclouds.com/devices/1051580320/datapoints',
      header: {
        'content-type': 'application/json',
        'api-key':'1ZXQyfKnqL1bqEV0D0JJqbL7pmc='
      },
      method: 'POST',
      data: JSON.stringify(data),//data数据转换成JSON格式
      success(res){
        console.log("成功",res.data)
      },
      fail(res){
        console.log("失败",res)
      }
    })
 },
  onLoad() {
    var that = this
    setInterval(function(){
      that.getinfo()
    },1000)
  }
})
