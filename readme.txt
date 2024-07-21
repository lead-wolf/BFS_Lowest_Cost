Struct Stade dùng để định nghĩa một nút trong đồ thị với 2 thuộc tính
    id là ký tự để biểu diễn tên node
    cost dùng để lưu chi phí của node

method operator là phương thức so sánh
    trong phương thức này sẽ so sánh node hiện tại và node được nhập vào
    hàm trả về true khi node hiện tại (this) có chi phí lớn hơn
                false khi node hiện  tại (this) có chi phí nhỏ hơn
    toán tử ">" để xác định thứ tự của các phần tử.
    hàng đợi ưu tiên sẽ sắp xếp các đối tượng State theo cost tăng dần

graph dùng kiểu map để lưu trữ đồ thị với cú pháp
    ký tự đầu tiên là node hiện tại
    tiếp theo là các vector chứa đỉnh mà đỉnh hiện tại có thể đi tới và chi phí của nó

successors dùng để tìm các node kề của node s đưa vào
    sau khi tiềm được sẽ đưa vào vector result
    hàm sẽ trả về 1 vector gồm tất cả các node kề và chi phí.

Hàm cost nhận vào hai tham số s1 và s2, đại diện cho hai trạng thái cần tính chi phí.
    Trong vòng lặp, nó duyệt qua các hàng xóm của trạng thái s1 trong đồ thị.
    Nếu tên của hàng xóm trùng khớp với tên của s2, hàm trả về giá trị chi phí tương ứng.
    Nếu không tìm thấy đường đi giữa s1 và s2, hàm trả về giá trị vô cùng

Trong hàm main
    Khởi tạo node thái bắt đầu và kết thúc
    gán cho vector path các đường đi tìm được
    kiểm tra nếu path không rỗng thì in đường đi ra
    ngược lại báo ko tìm thấy đường đi

Hàm BFS_Lowest_Cost
    unordered_map<char, State> previous: Lưu trạng thái trước đó của mỗi trạng thái (để tái tạo đường đi sau này).
    unordered_map<char, int> g: Lưu chi phí tới mỗi trạng thái từ trạng thái bắt đầu.
    Sau đó bắt đầu thuật toán tìm kiếm
        trong khi open_set không rỗng:
            Lấy trạng thái đầu tiên ra khỏi open_set.
            Nếu trạng thái hiện tại là trạng thái đích, tái tạo đường đi từ previous và trả về.

        Vòng lặp for duyệt qua mỗi trạng thái kế tiếp của trạng thái hiện tại (current).
            Biến succ là một trạng thái kế tiếp.
            tentative_g là tổng chi phí từ trạng thái bắt đầu đến current và chi phí từ current đến succ.
                Nó đại diện cho chi phí tạm thời để đi từ trạng thái bắt đầu đến succ thông qua current.
            Nếu succ chưa được duyệt hoặc tentative_g nhỏ hơn chi phí hiện tại của succ:
            Cập nhật previous[succ.id] để tái tạo đường đi.
            Cập nhật g[succ.id] với tentative_g.
            Tạo một trạng thái mới next_state với thông tin từ succ và chi phí mới.
            Đưa next_state vào open_set để xem xét tiếp.