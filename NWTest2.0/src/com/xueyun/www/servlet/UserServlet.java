package com.xueyun.www.servlet;


import com.xueyun.www.po.Time;
import com.xueyun.www.po.User;
import com.xueyun.www.exception.CustomerErrorMsgException;
import com.xueyun.www.service.UserService;
import org.apache.commons.beanutils.BeanUtils;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

@WebServlet(name = "UserServlet", urlPatterns = "/UserServlet")
public class UserServlet extends BaseServlet {
    //实例业务类代码
    private UserService userService = new UserService();

    //请求4：处理用户退出请求
    private void loginOut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        //销毁session
        request.getSession().invalidate();
        //跳转登录
        response.sendRedirect(request.getContextPath()+"/login.html");
    }


    //请求2：处理用户登录请求
    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {


            //2.获取登录的用户名与密码
            String name=request.getParameter("name");
            String sid = request.getParameter("sid");
            String password = request.getParameter("password");

            //3.调用业务层根据用户名与密码进行登录
            User loginUser = userService.login(name,sid, password);

            //4.获取返回数据判断登录用户是否为null
            if(loginUser!=null) {
                //   返回数据不为空null，登录成功将登录数据写入session
                request.getSession().setAttribute("name",loginUser.getName());
                request.getSession().setAttribute("sid",loginUser.getSid());
                //   返回true给前端
                response.getWriter().print("true");
            }

        } catch (CustomerErrorMsgException e) {
            //5.登录失败，返回自定义异常，直接将失败消息输出
            response.getWriter().print(e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();

            //6.登录失败，返回系统异常，直接抛出
            throw new RuntimeException(e);
        }
    }

    //请求1：处理用户注册的请求
    private void register(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            //1.获取表单提交所有用户数据封装到User对象中
            User user = new User();
            BeanUtils.populate(user,request.getParameterMap());

            //2.调用业务层实现用户注册
            boolean isRegister = userService.register(user);

            //3.获取业务层返回的结果,结果1：返回true,代表注册成功输出返回前端
            response.getWriter().print(isRegister);

        } catch (CustomerErrorMsgException e) {
            //e.printStackTrace(); 自定义不需要打印，因为不需要开发人员解决，所以不需要打印
            //结果2：返回自定义异常,将失败消息输出到前端
            response.getWriter().print(e.getMessage());

        } catch (Exception e) {
            e.printStackTrace();
            //结果3：返回系统异常,直接抛给前端
            throw new RuntimeException(e);
        }
    }

    //请求5：处理时间添加的请求
    private void time(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            //1.获取表单提交所有用户数据封装到User对象中
            Time time=new Time();
            BeanUtils.populate(time,request.getParameterMap());

            //2.调用业务层实现用户注册
            boolean isRegister = userService.time(time);

            //3.获取业务层返回的结果,结果1：返回true,代表注册成功输出返回前端
            response.getWriter().print(isRegister);

        } catch (Exception e) {
            e.printStackTrace();
            //结果3：返回系统异常,直接抛给前端
            throw new RuntimeException(e);
        }
    }

    //处理导师姓名查找
    private void search(HttpServletRequest request, HttpServletResponse response) throws Exception {
        //1.获取姓名
        String name=request.getParameter("name");
        Time timeuser=userService.search(name);

        if(timeuser!=null){

            System.out.println("");
        }
    }

    //删除用户
    private void delete(HttpServletRequest request,HttpServletResponse response) throws Exception {
        try {
            //1.获取id
            String sid=request.getParameter("user.getSid()");
            //2.调用service删除
            UserService userservice=new UserService();
            boolean flag=userservice.delete(sid);

            if(flag){
                //   返回true给前端
                response.getWriter().print("true");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
