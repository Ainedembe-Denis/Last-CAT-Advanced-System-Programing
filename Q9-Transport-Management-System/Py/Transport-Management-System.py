import os

# Vehicle Class
class Vehicle:
    def __init__(self, vid, vtype, capacity):
        self.id = vid
        self.type = vtype
        self.capacity = capacity

    def save_to_file(self, filename):
        try:
            # Using tabs to allow spaces in the vehicle type name
            with open(filename, "a") as f:
                f.write(str(self.id) + "\t" + str(self.type) + "\t" + str(self.capacity) + "\n")
            print("Vehicle saved successfully.")
        except Exception as e:
            print("Could not save to file:", e)

    @staticmethod
    def display_file(filename):
        print("\nAvailable Vehicles:")
        if not os.path.exists(filename):
            print("No vehicles recorded yet.")
            return
        
        try:
            with open(filename, "r") as f:
                for line in f:
                    parts = line.strip().split('\t')
                    if len(parts) == 3:
                        print("ID: " + parts[0] + " | Type: " + parts[1] + " | Capacity: " + parts[2])
        except Exception as e:
            print("Error reading file:", e)

# Main Execution
def run_app():
    # Find the current folder for the script
    try:
        current_dir = os.path.dirname(os.path.abspath(__file__))
    except NameError:
        current_dir = os.getcwd()
        
    data_file = os.path.join(current_dir, "vehicles.txt")

    print("TRANSPORT MANAGEMENT SYSTEM")
    print("---------------------------")
    
    try:
        count_str = input("Enter number of vehicles to add: ")
        if not count_str.strip():
            print("No count entered. Exiting...")
            return
            
        n = int(count_str)
        for i in range(n):
            print("\nEnter details for vehicle " + str(i+1) + ":")
            v_id = input("ID: ")
            v_type = input("Type: ")
            v_cap = input("Capacity: ")

            v = Vehicle(v_id, v_type, v_cap)
            v.save_to_file(data_file)

        # Show final results
        Vehicle.display_file(data_file)

    except ValueError:
        print("\nPlease enter a valid number.")
    except Exception as e:
        print("\nAn error occurred:", e)

    input("\nPress Enter to exit...")

if __name__ == "__main__":
    run_app()
