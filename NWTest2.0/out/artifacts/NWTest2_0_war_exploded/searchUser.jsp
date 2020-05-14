<%--
  Created by IntelliJ IDEA.
  User: 86135
  Date: 2020/5/9
  Time: 22:58
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="com.xueyun.www.po.User" %>
<%@ page import="java.util.*" %>
<%@ page import="com.xueyun.www.dao.UserDao" %>
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
    <!--导入jquery-->
    <script src="js/jquery-3.3.1.min.js"></script>
    <!--导入将jq对象转换为json字符串插件-->
    <script type="text/javascript" src="js/json.js"></script>
    <script type="text/javascript">
       function deleteUser(sid) {
           //安全提示
           if(confirm("您确定要删除该用户吗？")){
               $.post({
                   url:"UserServlet",
                   data:$("#delForm").serialize(),
                   success:function (result) {
                       if(result=="true"){
                           alert("成功删除");
                       }else {
                           $("#msg").html(result);
                       }
                   },
                   error:function () {
                       //结果3：返回系统异常，在error回调函数中弹出服务器忙
                       alert("服务器忙");
                   }
               })
           }
       }
    </script>

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
    </style>
</head>
<body>
<hr color="#9a0000" width=100% />

<div class="box2">
    <font color="#9a0000" size="20">欢迎登录导师预约系统</font>
</div>
<hr size="55px" noshade=false width="100%" color="#9a0000"/>

<table>
    <caption><b><font size="5px">用户注册信息表</font></b></caption>
    <tr>
        <th>姓名</th>
        <th>电话</th>
        <th>工学号</th>
        <th>学院</th>
        <th>专业</th>
        <th>操作</th>
    </tr>

    <%
        //创建对象
        UserDao dao=new UserDao();
        //接口List创建list对象，然后通过对象dao调用TitleDAO中的readFirstTitle（）方法，从而把返回的list赋予给list
        List<User> list=dao.readFist();
        //进行数据的遍历
        for(User user:list){
    %>
    <form id="delForm" method="post">
        <!--增加一个表单项存储请求标识符数据action-->
        <input type="hidden" name="action" value="delete">
    <tr>
        <td><%=user.getName()%></td>
        <td><%=user.getTel()%></td>
        <td><%=user.getSid()%></td>
        <td><%=user.getColloge()%></td>
        <td><%=user.getGrade()%></td>
        <td><a class="delBtn" href="javascript:deleteUser(<%=user.getSid()%>);">删除</a></td>
    </tr>
    </form>
    <%}
    %>
</table>

<div>
    <a href="home03.jsp">返回首页</a>
</div>

</body>
</html>
