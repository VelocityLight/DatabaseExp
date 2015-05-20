<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>主页</title>
<script src="http://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.8.0.js">
</script>
<script type="text/javascript">
function searchF(e){
	var username = document.getElementById("username").innerHTML;
	var password = document.getElementById("password").innerText;
	var friend_name = document.getElementById("friend_name").value;
	window.location.href = "search?username="+username+"&password="+password+"&friend_name="+friend_name;
}
function showfriends(e)
{
	var list_name = document.getElementById("list_name");
	var username = document.getElementById("username").innerHTML;
	var password = document.getElementById("password").innerText;
	window.location.href = "show?list_name="+e.innerHTML+"&username="+username+"&password="+password;
}
function response(){
	var message = document.getElementById("message").innerHTML;
	window.location.href = "response?message="+message;
}
function change(){
	var experience = document.getElementById("experience").innerHTML;
	window.location.href = "change?experience="+experience;
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
		<p>Search:<input type="text" id="friend_name" name="friend_name" /></p>
		<p><button onclick="searchF(this)">SearchFriend</button></p>
		<p>分组</p>
		<center>
		<table border="1">
			<s:iterator value="friendlist" id="String1" status = "status">
			<tr>
			<td>
				<p id="list_name"><p clickable="clickable" onclick="showfriends(this);"><s:property value="String1"/> </p> </p> 
				
			</td>
			</tr>
			</s:iterator>
		</table>
		<p>留言</p>
		<table border="1">
			<s:iterator value="message" id="String2" status = "status">
			<tr>
			<td>
				<p id="message"><p clickable="clickable" onclick="response();"><s:property value="String2"/> </p> </p> 
				
			</td>
			</tr>
			</s:iterator>
		</table>
		<p>经历</p>
		<table border="1">
			<s:iterator value="experience" id="String3" status = "status">
			<tr>
			<td>
				<p id="experience"><p clickable="clickable" onclick="change();"><s:property value="String3"/> </p> </p> 
				
			</td>
			</tr>
			</s:iterator>
		</table>
		<p>兴趣</p>
		<table border="1">
			<s:iterator value="hobby" id="String4" status = "status">
			<tr>
			<td>
				<p id="hobby"><p clickable="clickable" onclick="addhobby();"><s:property value="String4"/> </p> </p> 
				
			</td>
			</tr>
			</s:iterator>
		</table>
		</center>
	</body>
</html>