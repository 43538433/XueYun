package com.xueyun.www.servlet;

import com.xueyun.www.po.User;

import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;


public class BaseServlet extends HttpServlet {
    @Override
    public void service(ServletRequest req, ServletResponse res)throws ServletException, IOException {
        try {
            //将父接口转换为子接口
            HttpServletRequest request = (HttpServletRequest) req;
            HttpServletResponse response = (HttpServletResponse) res;

            //获取action
            String action = request.getParameter("action");

            //目标：根据获取action的方法名字，使用反射调用方法自动执行
            //1.获取servlet的字节码对象
            //this 当前实例对象UserServlet
            Class clazz = this.getClass();

            //2.根据处理请求方法名字字符串获取Method反射对象
            Method method = clazz.getDeclaredMethod(action, HttpServletRequest.class, HttpServletResponse.class);
            method.setAccessible(true);

            //3.调用Method的invoke方法自动执行方法

            try {
                method.invoke(this,request,response);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }

    }
}