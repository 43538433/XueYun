package com.xueyun.www.exception;

public class CustomerErrorMsgException extends Exception {

    public CustomerErrorMsgException(){

    }

    public CustomerErrorMsgException(String errorMsg){
        super(errorMsg);
    }
}
