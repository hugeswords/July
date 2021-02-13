# 冒泡排序
本质：大数下沉，导致小数慢慢上升  
原理：从第一元素开始，和下一个元素比较，如果大于，则进行交换，直至最后一个元素，此时最后一个元素就是最大的元素。  
下一轮重复以上操作，但是最后一个元素已经是最大的元素了，所以只需要比较到N-1的位置。  
时间复杂度：n + (n-1) + (n-2) …… = n(n-1)/2 =O(n*n)  
空间复杂度：O(n)  
