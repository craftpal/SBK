   M S B A M L   `   `   `  ����  GenInputJSON    GenInputJSON.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   -   5          � Title$  最適骨化くん��5   	   $	��350��6   $	��430��6%   $y�Visible=�61    � WindowStyle$ 
ToolWindow=�6F   $	��430��6_   $	��250��6n   .��5      �  � RowDefinitions 5   
   �� 5      $
��auto �6   �� 5      .+�5
   
   � $
��auto��6   $��5,5,5,0q�6   $
��auto��6.   $��1��6;    � ColumnDefinitions 5      �� 5      $��1* �6#   $��90��6.   �� 5      $
��200* �6#   $	��200��60    5      �� 5      $��15 �6    �� 5      $��1* �6    $	��150��6,   �� 5      $��15 �6    �� 5      $��1* �6    �� 5      $��36 �6    .+�5      �� -   5         ��Name$ 	tb_base_x��5      $��20��6)   $��	0,25,10,0q�65   $��1��6H    �� TextWrapping$
 Wrap=�6U   $��0��6i   $	��Top=�6r   $��0q�6�   $
��Left=�6�   $��50��6�   $��4��6�   6�   �� 5      -   5         ��Name$ groupBox��5      $��密度:重み��6)   $
��Left=�68   $��	0,45,10,0q�6S   $��1��6f   $	��Top=�6s   $	��108��6�   $��3��6�   $��85��6�   $��2��6�   .��5      �  5      �� 5      $��1* �6(   �� 5      $��1* �6(   �� 5      $��1* �6(   �� 5      $��1* �6(   .+�5       �� $��繊維方向(X)��6   $��0,0,0,0q�6.   $��0��6?   $	��Top=�6L   $��4��6d   �� 5!      -   5        $ tb_weight_x��5!      $��20��63   $��0,0,0,0q�6?   $��1��6P   $
 Wrap=�6]   $��1��6q   $	��Top=�6z   $��0q�6�   $
��Left=�6�   $��50��6�   $��4��6�   6�   �� 5"      $��繊維垂直(Y)��6   $��0,0,0,0q�6.   $��2��6?   $	��Top=�6L   $��4��6d   �� 5#      -   5        $ tb_weight_y��5#      $��20��63   $��0,0,0,0q�6?   $��3��6P   $
 Wrap=�6]   $��10��6q   $	��Top=�6{   $��0q�6�   $
��Left=�6�   $��50��6�   $��4��6�   6�   5$      5%      &   System.Windows.Controls.DataGrid  5&      -   5          Name$ grid_target��5&      $	��0,3q�6,   $��16(�69   $��1��6G   $��1��6W      AutoGenerateColumns .  	   Columns	 5'      0  *System.Windows.Controls.DataGridTextColumn  5(      ,  &System.Windows.Controls.DataGridColumn
   Header$
 繊維方向(X)��6)   1  +System.Windows.Controls.DataGridBoundColumn   Binding 5)   )   �� *x+  5*      $
 繊維垂直方向(Y)��6)    5+   )   �� *y+5-        5.      -   5        $ 
grid_parts��5.      $��0,3,0,0q�6+   $��Stretch=�6<   $��Stretch=�6a   $��16(�6�   $��3��6�   $��1��6�    .  	 5/        50      $
 レイヤー名��6)    51   )   �� *id+  52      $
 繊維方向(X)��6)    53   )   �� *x+  54      $
 繊維垂直方向(Y)��6)    55   )   �� *y+57      �� 58      $��X��6   $��0q�6    $��1��6+   $	��Top=�68   $��4��6P   �� 59      $��差分範囲��6   $��0q�6#   $��1��6.   $��0q�6>   �� 5:      $��切出部位��6   $��0q�6#   $��0q�6.   $��1��6:   $��2��6J   �� 5;      $��基準範囲��6   $��0q�6#   �� 5<      -   5         ��Name$ 	btOutPath��5<      $	��...��6(   $
��Left=�66   $��0q�6Q   $��3��6\   $��Bottom=�6i   $��2��6�   $��23��6�   $��20��6�   6�   �� 5=      -	   5        $ tb_path��5=      $
��Left=�6'   $��23��6B   $��3��6N   $�� ��6[   $��50��6c   $��Bottom=�6n   $��20,0,0,0q�6�   $��2��6�   �� 5>      -
   5        $ 	start_gen��5>      $��生成開始��6(   $	��0,6q�67   $
��auto��6D    J� RenderTransformOrigin$ 0.217,0.833&�6Q   $��24��6u   $��4��6�   $��Center=�6�   $��Center=�6�   $��2��6�   5?      o� 5@   
   .@�5A      m� $��ファイル(_F)��6   .@�5B      m� -   5         m�Name$ miOpen��5B      $��
開く(_O)��6+   6;   m� 5C      -   5        $ miSave��5C      $��
保存(_S)��6+   6;   m� 5D      -   5        $ 	miOpenAdd��5D      $��切出部位のみ追加��6.   6@   5E      5F      5G      5H      