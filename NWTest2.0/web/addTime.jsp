<%--
  Created by IntelliJ IDEA.
  User: 86135
  Date: 2020/5/13
  Time: 18:37
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>添加时间</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
    <link rel="stylesheet" href="css/home.css">
    <!--导入jquery-->
    <script src="js/jquery-3.3.1.min.js"></script>
    <!--导入将jq对象转换为json字符串插件-->
    <script type="text/javascript" src="js/json.js"></script>
    <script type="text/javascript">
        $(function () {
            //1.给“注册”按钮注册点击事件
            $("#addBtn").click(function () {
                //提交异步的注册用户请求给后端
                $.post({
                    url:"UserServlet",
                    data:$("#timeForm").serialize(),//表单注册的用户数据+请求标识符action
                    success:function (result) {

                        //4.获取服务器异步请求返回的结果
                        if(result=="true"){
                            //结果1：返回true
                            alert("添加成功");
                        }else{
                            //结果2：返回注册失败的消息，更新到页面上显示让用户解决
                            $("#msg").html(result);
                        }
                    },
                    error:function () {
                        //结果3：返回系统异常，在error回调函数中弹出服务器忙
                        alert("服务器忙");
                    }
                });
            });
        });
    </script>

    <style type="text/css">
        .box1{float: left;padding: 0px 20px;}
        .box2{float: left;padding: 0px 0px;letter-spacing: 30px}
        input{
            box-sizing:border-box;
            border: 2px solid #9a0000;
            border-radius: 5px;
            padding: 9px 15px;
        }
    </style>
</head>
<body>

<hr color="#9a0000" width=100% />

<div class="box2">
    <font color="#9a0000" size="20">欢迎登录导师预约系统</font>
</div>
<hr size="55px" noshade=false width="100%" color="#9a0000"/>
<form id="timeForm" method="post">
    <!--增加一个表单项存储请求标识符数据action-->
    <input type="hidden" name="action" value="time">
    <div>
        <%String name=(String)session.getAttribute("name");%>
        <%String sid=(String)session.getAttribute("sid");%>
        <input type="text" id="name" name="name" readonly="readonly" value="<%=name%>">
        <input type="text" id="sid" name="sid" readonly="readonly" value="<%=sid%>">
        <input type="text" id="colloge" name="colloge" placeholder="请输入学院">
        <input type="text" id="time" name="time" placeholder="请输入时间">
        <input type="button" value="添加" id="addBtn" class="submit">
    </div>
</form>

<style type="text/css">
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

</style>

<table>
    <caption><b><font size="5px">时间添加信息表</font></b></caption>
    <tr>
        <th>姓名</th>
        <th>学号</th>
        <th>学院</th>
        <th>时间</th>
        <th>操作</th>
    </tr>

    <tr>
        <td>xxx</td>
        <td>xxxxxxxxxx</td>
        <td>计算机学院</td>
        <td>2020-05-08</td>
        <td>
            <!--<input id="delBtn" type="button" class="submit" value="删除">-->
            删除
        </td>
    </tr>
</table>

<script>
    /*
    分析：
    1.添加：
        1.给添加按钮绑定单击事件
        2.获取文本框的内容
        3.创建td,设置td的文本为文本框的内容
        4.创建tr
        5.将td添加到tr中
        6.获取table，将tr添加到table中

    2.删除
        1.确定点击的是哪个超链接
        2.怎么删除？
           removeChild();通过父节点删除子节点
     */

    //1.获取addBtn按钮
    document.getElementById("addBtn").onclick=function () {
        //2.获取文本框的内容
        var name=document.getElementById("name").value;
        var sid=document.getElementById("sid").value;
        var colloge=document.getElementById("colloge").value;
        var time=document.getElementById("time").value;

        //3.创建td,赋值td的标签
        //name的td
        var td_name=document.createElement("td");
        var text_name=document.createTextNode(name);
        td_name.appendChild(text_name);
        //sid的td
        var td_sid=document.createElement("td");
        var text_sid=document.createTextNode(sid);
        td_sid.appendChild(text_sid);
        //colloge的td
        var td_colloge=document.createElement("td");
        var text_colloge=document.createTextNode(colloge);
        td_colloge.appendChild(text_colloge);
        //time的td
        var td_time=document.createElement("td");
        var text_time=document.createTextNode(time);
        td_time.appendChild(text_time);
        //a标签的td
        var td_a=document.createElement("td");
        var ele_a=document.createElement("a");
        ele_a.setAttribute("href","javascript:void(0);");
        ele_a.setAttribute("onclick","delTr(this);");
        var text_a=document.createTextNode("删除");
        ele_a.appendChild(text_a);
        td_a.appendChild(ele_a);

        //4.创建tr
        var tr=document.createElement("tr");

        //5.添加td到tr中
        tr.appendChild(td_name);
        tr.appendChild(td_sid);
        tr.appendChild(td_colloge);
        tr.appendChild(td_time);
        tr.appendChild(td_a);

        //6.获取table
        var table=document.getElementsByTagName("table")[0];
        table.appendChild(tr);
    }
    //删除方法
    function delTr(obj) {
        //获取的父节点(td)的父节点的(tr)的父节点(table)
        var table=obj.parentNode.parentNode.parentNode;
        var tr=obj.parentNode.parentNode;
        table.removeChild(tr);
    }
</script>

<div>
    <a href="home02.jsp">返回首页</a>
</div>


</body>
</html>
