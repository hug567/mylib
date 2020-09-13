## HTML基础

### 1、HTML元素：

#### 1.1、\<link>：链接外部样式文件

```html
<link rel="stylesheet" type="text/css" href="theme.css">
```

支持的常用属性有：
```html
rel        <!-- 被链接文档与当前文档间的关系，必选 -->
type       <!-- 被链接文档的MIME类型 -->
href       <!-- 被链接文档的位置 -->
```

#### 1.2、\<p>：段落

```html
<p>这是一个段落。</p>
```

#### 1.3、\<div>：区块

```html
<div style="color:#00FF00">
    <p>current text color will be green</p>
</div>
```