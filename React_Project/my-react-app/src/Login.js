import React, { useState } from 'react';
import './Login.css';

const Login = () => {
  const [formData, setFormData] = useState({
    username: '',
    password: '',
  });
  const [errors, setErrors] = useState({
    username: '',
    password: '',
  });
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [loginError, setLoginError] = useState('');

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData({
      ...formData,
      [name]: value,
    });
    // 清除当前字段的错误
    setErrors({
      ...errors,
      [name]: '',
    });
    // 清除登录错误
    setLoginError('');
  };

  const validateForm = () => {
    let valid = true;
    const newErrors = { ...errors };

    if (!formData.username.trim()) {
      newErrors.username = '用户名不能为空';
      valid = false;
    }

    if (!formData.password) {
      newErrors.password = '密码不能为空';
      valid = false;
    } else if (formData.password.length < 6) {
      newErrors.password = '密码至少需要6个字符';
      valid = false;
    }

    setErrors(newErrors);
    return valid;
  };

  // 模拟API调用
  const mockLoginApi = async (username, password) => {
    // 这里模拟API响应延迟
    await new Promise(resolve => setTimeout(resolve, 1000));
    
    // 模拟注册用户数据库
    const registeredUsers = [
      { username: 'user1', password: 'password1' },
      { username: 'test', password: 'test123' },
    ];
    
    const user = registeredUsers.find(u => u.username === username);
    
    if (!user) {
      throw new Error('该用户名未注册');
    }
    
    if (user.password !== password) {
      throw new Error('密码错误');
    }
    
    return { success: true, token: 'mock-token' };
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoginError('');

    if (validateForm()) {
      setIsSubmitting(true);
      
      try {
        const response = await mockLoginApi(formData.username, formData.password);
        console.log('登录成功', response);
        // 实际应用中这里会存储token并重定向
      } catch (error) {
        // 根据错误类型设置不同的错误消息
        if (error.message === '该用户名未注册') {
          setLoginError('该用户名未注册，请检查或注册新账号');
          setErrors({
            ...errors,
            username: '用户名未注册',
          });
        } else if (error.message === '密码错误') {
          setLoginError('密码错误，请重新输入');
          setErrors({
            ...errors,
            password: '密码错误',
          });
        } else {
          setLoginError('登录失败，请稍后重试');
        }
      } finally {
        setIsSubmitting(false);
      }
    }
  };

  return (
    <div className="login-container">
      <div className="login-form">
        <h2>用户登录</h2>
        {loginError && (
          <div className={`error-message ${loginError.includes('未注册') ? 'account-error' : 'password-error'}`}>
            {loginError}
          </div>
        )}
        
        <form onSubmit={handleSubmit}>
          <div className="form-group">
            <label htmlFor="username">用户名</label>
            <input
              type="text"
              id="username"
              name="username"
              value={formData.username}
              onChange={handleChange}
              className={errors.username ? 'error' : ''}
              autoComplete="username"
            />
            {errors.username && (
              <span className={`error-message ${errors.username === '用户名未注册' ? 'account-error' : ''}`}>
                {errors.username}
              </span>
            )}
          </div>
          
          <div className="form-group">
            <label htmlFor="password">密码</label>
            <input
              type="password"
              id="password"
              name="password"
              value={formData.password}
              onChange={handleChange}
              className={errors.password ? 'error' : ''}
              autoComplete="current-password"
            />
            {errors.password && (
              <span className={`error-message ${errors.password === '密码错误' ? 'password-error' : ''}`}>
                {errors.password}
              </span>
            )}
          </div>
          
          <button 
            type="submit" 
            className="login-button"
            disabled={isSubmitting}
          >
            {isSubmitting ? '登录中...' : '登录'}
          </button>
        </form>
        
        <div className="additional-options">
          <a href="/forgot-password">忘记密码?</a>
          <span> | </span>
          <a href="/register">注册新账号</a>
        </div>
      </div>
    </div>
  );
};

export default Login;