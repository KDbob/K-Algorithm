# N皇后的局部搜索

> 超越经典搜索算法

## 爬山法

__function__ HILL-CLIMBING(_problem_) __returns__ a state that is a local maximum  
&emsp;_current_ &larr; _problem_.INITIAL\-STATE  
&emsp;__loop do__  
&emsp;&emsp;&emsp;_neighbor_ &larr; a highest\-valued successor of _current_  
&emsp;&emsp;&emsp;_if_ VALUE(_neighbour_) &le; VALUE(_current_) __then return__ _current_  
&emsp;&emsp;&emsp;_current_ &larr; _neighbor_  

邻域

