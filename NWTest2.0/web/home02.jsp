<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="java.util.Date" %><%--
  Created by IntelliJ IDEA.
  User: 86135
  Date: 2020/5/13
  Time: 18:37
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta charset="UTF-8">
    <title>导师预约系统</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
    <link rel="stylesheet" href="css/home.css">
    <style type="text/css">
        .box1{float: right;padding: 40px 20px;letter-spacing: 5px}
        .box2{float: left;padding: 20px 20px;letter-spacing: 30px}
        .box3{float: left;background-color:#9a0000;
            -webkit-box-sizing: border-box;
            -moz-box-sizing: border-box;
            box-sizing: border-box;
            width: 130px;height: 545px; border: 10px }
    </style>
</head>
<body>
<hr color="#9a0000" width=100% />
<div class="box1">
    <%String name=(String)session.getAttribute("name");%>
    <%
        Date date=new Date();
        SimpleDateFormat dateFormat=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String now=dateFormat.format(date);
    %>
    <tr>
        <td>
            <font color="#9a0000" size="4"><%=name%>Welcome,</font>
            <font color="#9a0000" size="4">登录时间:<%=now%></font>
        </td>
    </tr>
</div>
<div class="box2">
        <tr>
            <td>
                <font color="#9a0000" size="20">欢迎登录导师预约系统</font>
            </td>
        </tr>

</div>
    <hr size="55px" noshade=false width="100%" color="#9a0000"/>
<div class="content_body">
    <div class="box3" id="leftNav">
        <ul class="outside">
            <br>
            <br>
            <li>
                <a href="addTime.jsp"><b>&nbsp;&nbsp;&nbsp;&nbsp;<font color="#ABEED9">添加时间</font></b></a>
            </li>
            <br>
            <br>
            <li id="dispose">
                <a href="#"><b>&nbsp;&nbsp;&nbsp;&nbsp;<font color="#ABEED9">处理预约请求</font></b></a>
            </li>
            <br>
            <br>
            <li id="showTime">
                <a href="#"><b>&nbsp;&nbsp;&nbsp;&nbsp;<font color="#ABEED9">近期预约计划</font></b></a>
            </li>
            <br>
            <br>
            <li id="massge">
                <a href="#"><b>&nbsp;&nbsp;&nbsp;&nbsp;<font color="#ABEED9">通知信息</font></b></a>
            </li>
        </ul>
    </div>
</div>
</body>
</html>