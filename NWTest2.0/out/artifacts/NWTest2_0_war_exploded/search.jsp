<%--
  Created by IntelliJ IDEA.
  User: 86135
  Date: 2020/5/9
  Time: 22:58
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="com.xueyun.www.po.Time" %>
<%@ page import="java.util.*" %>
<%@ page import="com.xueyun.www.dao.TimeDao" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String path=request.getContextPath();
    //获得应用的根url,以后寻找资源的相对路径就是<base>所描述的
    String basepath=request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";

%>
<html>
<head>
    <title>查询导师时间</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
    <link rel="stylesheet" href="css/home.css">

    <style type="text/css">
        .box1{float: left;padding: 20px 39px;}
        .box2{float: left;padding: 20px 20px;letter-spacing: 30px}
        table{
            border: 5px solid;
            color: #9a0000;
            margin: auto;
            width: 1000px;
        }
        td,th{
            text-align: center;
            border: 2px solid;
        }
        div{
            text-align: center;
            margin: 20px;
        }
        #orderTime{
            box-sizing: border-box;
            border: 5px;
            width: 50px;
            font-size: 15px;
            color: #9a0000;
        }
        input{
            box-sizing:border-box;
            border: 2px solid #9a0000;
            border-radius: 5px;
            padding: 9px 15px;
        }
    </style>

    <script type="text/javascript">
        function show_confirm() {
            var r=confirm("确定要预约吗？");
            if(r==true){
                alert("预约成功！");
            }else {
                alert("已取消预约！");
            }
        }
        $(function () {
            $("#searchBtn").click(function () {
                //提交异步请求给后端
                $.post({
                    url:"UserServlet",
                    data:$("#searchForm").serialize(),
                    success:function (result) {
                        //4.获取服务器异步请求返回的结果
                        if(result=="true"){

                        }else{

                            $("#msg").html(result);
                        }

                    },
                    error:function () {
                        //结果3：返回系统异常，在error回调函数中弹出服务器忙
                        alert("服务器忙，请稍后再试...");
                    }
                });

            });
        });

    </script>
</head>
<body>
<hr color="#9a0000" width=100% />
<div class="box2">
    <font color="#9a0000" size="20">欢迎登录导师预约系统</font>
</div>
<hr size="55px" noshade=false width="100%" color="#9a0000"/>

<form id="searchForm01" method="post">
    <!--增加一个表单项存储请求标识符数据action-->
    <input type="hidden" name="action" value="search">
    <div>
        <label for="keyname">按姓名查找：</label>
        <input type="text" id="keyname" name="keyname" placeholder="请输入姓名">
        <input type="button" value="搜索" id="searchBtn" class="submit">
    </div>
</form>

<table>
    <caption><b><font size="5px">导师时间信息表</font></b></caption>

    <tr>
        <th>编号</th>
        <th>姓名</th>
        <th>学院</th>
        <th>时间</th>
        <th>操作</th>
    </tr>

    <%
        //创建对象
        TimeDao dao=new TimeDao();
        //接口List创建list对象，然后通过对象dao调用TitleDAO中的readFirstTitle（）方法，从而把返回的list赋予给list
        List<Time> list=dao.readFist();
        //进行数据的遍历
        int i=1;
        for(Time time:list){

    %>

    <tr>
        <td><%=i%></td>
        <td><%=time.getName()%></td>
        <td><%=time.getColloge()%></td>
        <td><%=time.getTime()%></td>
        <td>
            <button id="orderTime" type="button"  onclick="show_confirm()">预约</button>
        </td>
    </tr>
    <% i++;%>
    <%}
    %>
</table>

<div>
    <a href="home01.jsp">返回首页</a>
</div>

</body>
</html>
