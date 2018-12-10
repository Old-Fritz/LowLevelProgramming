%define lastPtr 0
%macro colon 2
%define tempLabel %2
%%tempLabel:
dq lastPtr
db %1, 0
%define lastPtr %%tempLabel
%undef tempLabel
%endmacro
