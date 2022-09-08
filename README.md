# sudoku_cpp

- C++ 버전 스도쿠 풀이 프로그램입니다.
- 저번 C버전 보다 업그레이드하였으며 여러가지 함수들을 이용해 크기에 상관없이 풀이하여 보여줍니다.
- 다만 크기가 클 경우 풀이 속도가 오래걸릴 수 있습니다.

함수 리스트
split() -> 문자열을 분리해줍니다.
Row_Check() -> 1차원배열(가로 줄)을 체크합니다.
Col_Check() -> 2차원배열(세로 줄)을 체크합니다.
Square_Check() -> 2차원배열 중 각 구역(3x3)을 체크합니다.
Zero_Check() -> 2차원배열의 빈칸을 파악합니다.
Row_Col_Clear() -> 스도쿠를 풀기 위해 공백칸 리스트와 들어갈 수 있는 숫자 리스트가 있는데 공백 칸 리스트 중 숫자가 들어있는 경우 공백칸 리스트에서 제거합니다.
Square_Clear() -> 각 구역의 공백칸(nx3)을 모두 합쳐서 중복된 모든 요소를 제거하고 남은 수가 1개면 result에 값 넣고 없앱니다.
Square_Clear_2() -> 각 구역의 숫자 칸을 공백 칸의 리스트에서 지웁니다.
Row_Blank_Clear() -> 각 행의 공백 칸 중 어쩔 수 없이 어떤 숫자가 들어가는 칸을 찾아 적용시켜줍니다.
Blank_Clear() -> 공백 칸 리스트의 value가 0개이면 없애고, 1개이면 result에 값을 넣고 없앱니다.
Input_Value() -> 공백 칸에 들어갈 수 있는 숫자 모두 넣어보기

그 외 print 및 설정 관련 함수
