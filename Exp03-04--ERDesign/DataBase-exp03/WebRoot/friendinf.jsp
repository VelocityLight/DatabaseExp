<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>friend_inf</title>
<script src="http://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.8.0.js">
</script>
<script type="text/javascript">
function Returnto()
{
	var username = document.getElementById("username").innerHTML;
	var password = document.getElementById("password").innerHTML;
	window.location.href = "login?username="+username+"&password="+password;
}
</script>
</head>
	<style>
		body{ background-color:#FFCC99; }
		h1,h2 { text-align:center;font-family:"Comic Sans MS", cursive, sans-serif;}	
		p {
			line-height:150%;
			text-align:center; font-family:"Comic Sans MS", cursive, sans-serif;
		}
		tr,td { text-align:center;font-family:"Comic Sans MS", cursive, sans-serif;}
	</style>
	
	<body>
		<h1>个人主页</h1>
		<p id="username"><s:property value = "username"/></p>
		<p id="password"><s:property value = "password"/></p>
		<center>
		<p>经历</p>
		<table border="1">
			<s:iterator value="experience" id="String3" status = "status">
			<tr>
			<td>
				<s:property value="String3"/>
			</td>
			</tr>
			</s:iterator>
		</table>
		<p>兴趣</p>
		<table border="1">
			<s:iterator value="hobby" id="String4" status = "status">
			<tr>
			<td>
				<s:property value="String4"/>
			</td>
			</tr>
			</s:iterator>
		</table>
		<p>留言状态</p>
		<table border="1">
			<s:iterator value="friendstate" id="String5" status = "status">
			<tr>
			<td>
				<s:property value="String5"/>
			</td>
			</tr>
			</s:iterator>
		</table>
		<button onclick="Returnto()">ReturnBack</button>
		</center>
	</body>
</html>