import tkinter as tk
from tkinter import ttk
import json
import threading
# import time
from queue import Queue
import os

class AutoSaver:
    def __init__(self, save_func, interval=0):
        """
        Automatic background saver
        
        Args:
            save_func: Function to call for saving
            interval: Save interval in seconds
        """
        self.save_func = save_func
        self.interval = interval
        self.queue = Queue()
        self.stop_event = threading.Event()
        self.thread = threading.Thread(target=self._run, daemon=True)
        self.thread.start()
    
    def _run(self):
        """Background saving thread"""
        while not self.stop_event.is_set(): 
            # time.sleep(self.interval)
            if not self.queue.empty():
                self.queue.get()  # Clear any pending requests
                self.save_func()
    
    def request_save(self):
        """Request a save operation"""
        self.queue.put(True)
    
    def stop(self):
        """Stop the autosaver"""
        self.stop_event.set()
        self.thread.join()

class ConfigurableButton:
    def __init__(self, parent, config, autosaver):
        """
        Create a configurable button widget with automatic state saving
        
        Args:
            parent: Parent widget
            config: Dictionary containing:
                - x: Top-left x position
                - y: Top-left y position
                - width: Button width
                - height: Button height
                - text: Button text
                - variable: Tkinter variable to bind to
                - command: Optional command to execute
                - label: Optional label text
                - label_pos: 'top' or 'bottom' for label position
            autosaver: AutoSaver instance for automatic state saving
        """
        self.config = config
        self.autosaver = autosaver
        self.variable = config.get('variable', tk.BooleanVar(value=False))
        
        # Create label if specified
        if config.get('label'):
            lbl_y = config['y'] - 20 if config.get('label_pos', 'top') == 'top' else config['y'] + config['height'] + 5
            self.label = ttk.Label(parent, text=config['label'])
            self.label.place(x=config['x'], y=lbl_y)
        
        # Create button
        self.button = ttk.Button(
            parent,
            text=config['text'],
            width=config['width'],
            command=self._execute_commands
        )
        self.button.place(x=config['x'], y=config['y'], width=config['width'], height=config['height'])
        
        # Update button appearance based on variable
        self._update_appearance()
        self.variable.trace_add('write', self._on_state_change)
    
    def _execute_commands(self):
        """Toggle variable and execute any additional command"""
        self.variable.set(not self.variable.get())
        if 'command' in self.config:
            self.config['command']()
    
    def _on_state_change(self, *args):
        """Handle state changes and trigger auto-save"""
        self._update_appearance()
        self.autosaver.request_save()
    
    def _update_appearance(self):
        """Update button appearance based on variable value"""
        if self.variable.get():
            self.button.config(text=f"{self.config['text']} (ON)", style='Toggle.TButton')
        else:
            self.button.config(text=f"{self.config['text']} (OFF)", style='')

class PushButton:
    def __init__(self, parent, config, autosaver):
        """
        Create a pushbutton widget with automatic state saving
        
        Args:
            parent: Parent widget
            config: Dictionary containing:
                - x: Top-left x position
                - y: Top-left y position
                - width: Button width
                - height: Button height
                - text: Button text
                - variable: Tkinter variable to bind to
                - command: Optional command to execute
                - label: Optional label text
                - label_pos: 'top' or 'bottom' for label position
            autosaver: AutoSaver instance for automatic state saving
        """
        self.config = config
        self.autosaver = autosaver
        self.variable = config.get('variable', tk.BooleanVar(value=False))
        
        # Create label if specified
        if config.get('label'):
            lbl_y = config['y'] - 20 if config.get('label_pos', 'top') == 'top' else config['y'] + config['height'] + 5
            self.label = ttk.Label(parent, text=config['label'])
            self.label.place(x=config['x'], y=lbl_y)
        
        # Create button
        self.button = ttk.Button(
            parent,
            text=config['text'],
            width=config['width']
        )
        self.button.place(x=config['x'], y=config['y'], width=config['width'], height=config['height'])
        
        # Bind button press and release events
        self.button.bind('<ButtonPress>', self._on_press)
        self.button.bind('<ButtonRelease>', self._on_release)
    
    def _on_press(self, event):
        """Handle button press event"""
        self.variable.set(True)
        self.autosaver.request_save()
    
    def _on_release(self, event):
        """Handle button release event"""
        self.variable.set(False)
        self.autosaver.request_save()

class ToggleButton:
    def __init__(self, parent, config, autosaver):
        """
        Create a toggle button widget with automatic state saving
        
        Args:
            parent: Parent widget
            config: Dictionary containing:
                - x: Top-left x position
                - y: Top-left y position
                - width: Button width
                - height: Button height
                - text: Button text
                - variable: Tkinter variable to bind to
                - command: Optional command to execute
                - label: Optional label text
                - label_pos: 'top' or 'bottom' for label position
            autosaver: AutoSaver instance for automatic state saving
        """
        self.config = config
        self.autosaver = autosaver
        self.variable = config.get('variable', tk.IntVar(value=1))
        self.states = [1, 2, 3]
        self.current_state = 0
        
        # Create label if specified
        if config.get('label'):
            lbl_y = config['y'] - 20 if config.get('label_pos', 'top') == 'top' else config['y'] + config['height'] + 5
            self.label = ttk.Label(parent, text=config['label'])
            self.label.place(x=config['x'], y=lbl_y)
        
        # Create button
        self.button = ttk.Button(
            parent,
            text=config['text'],
            width=config['width']
        )
        self.button.place(x=config['x'], y=config['y'], width=config['width'], height=config['height'])
        
        # Bind button press event
        self.button.bind('<ButtonPress>', self._on_press)
    
    def _on_press(self, event):
        """Handle button press event"""
        self.current_state = (self.current_state + 1) % len(self.states)
        self.variable.set(self.states[self.current_state])
        self.autosaver.request_save()

class ConfigurableSlider:
    def __init__(self, parent, config, autosaver):
        """
        Create a configurable slider widget with automatic state saving
        
        Args:
            parent: Parent widget
            config: Dictionary containing:
                - x: Top-left x position
                - y: Top-left y position
                - width: Slider width
                - height: Slider height
                - min_val: Minimum value
                - max_val: Maximum value
                - variable: Tkinter variable to bind to
                - label: Optional label text
                - label_pos: 'top' or 'bottom' for label position
                - resolution: Slider resolution (default 1)
            autosaver: AutoSaver instance for automatic state saving
        """
        self.config = config
        self.autosaver = autosaver
        self.variable = config.get('variable', tk.DoubleVar(value=(config['min_val'] + config['max_val']) / 2))
        
        # Create label if specified
        if config.get('label'):
            lbl_y = config['y'] - 20 if config.get('label_pos', 'top') == 'top' else config['y'] + config['height'] + 5
            self.label = ttk.Label(parent, text=config['label'])
            self.label.place(x=config['x'], y=lbl_y)
        
        # Create value display
        self.value_label = ttk.Label(parent, textvariable=self.variable)
        value_y = config['y'] - 40 if config.get('label_pos', 'top') == 'top' else config['y'] + config['height'] + 25
        self.value_label.place(x=config['x'], y=value_y)
        
        # Create slider
        self.slider = ttk.Scale(
            parent,
            from_=config['min_val'],
            to=config['max_val'],
            variable=self.variable,
            length=config['width'],
            command=self._update_value
        )
        self.slider.place(x=config['x'], y=config['y'], width=config['width'], height=config['height'])
        
        # Setup variable tracing
        self.variable.trace_add('write', self._on_value_change)
    
    def _update_value(self, value):
        """Update value with proper resolution"""
        resolution = self.config.get('resolution', 1)
        rounded = round(float(value) / resolution) * resolution
        self.variable.set(rounded)
    
    def _on_value_change(self, *args):
        """Handle value changes and trigger auto-save"""
        self.autosaver.request_save()

class StateSaverApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Auto-Saving State Manager")
        self.root.geometry("1050x360")
        
        # Configure styles
        self._configure_styles()
        
        # Initialize variables
        self.button_vars = {}
        self.slider_vars = {}
        
        # Create autosaver
        self.autosaver = AutoSaver(self.save_states, interval=0)
        
        # Create widgets
        self._create_widgets()
        
        # Load saved states
        self.load_states()
        
        # Setup window close handler
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
    
    def _configure_styles(self):
        """Configure custom widget styles"""
        style = ttk.Style()
        style.configure('Toggle.TButton', foreground='green', font=('Arial', 10, 'bold'))
    
    def _create_widgets(self):
        """Create all buttons and sliders"""
        
        # Function buttons
        self.button_vars['f1'] = tk.BooleanVar(value=False)
        self.button1 = PushButton(self.root, {
            'x': 50,
            'y': 50,
            'width': 120,
            'height': 40,
            'text': 'F1',
            'variable': self.button_vars['f1'],
            'label': 'F1',
            'label_pos': 'top'
        }, self.autosaver)

        self.button_vars['f2'] = tk.BooleanVar(value=False)
        self.button2 = PushButton(self.root, {
            'x': 50,
            'y': 120,
            'width': 120,
            'height': 40,
            'text': 'F2',
            'variable': self.button_vars['f2'],
            'label': 'F2',
            'label_pos': 'top'
        }, self.autosaver)

        self.button_vars['f3'] = tk.BooleanVar(value=False)
        self.button3 = PushButton(self.root, {
            'x': 50,
            'y': 190,
            'width': 120,
            'height': 40,
            'text': 'F3',
            'variable': self.button_vars['f3'],
            'label': 'F3',
            'label_pos': 'top'
        }, self.autosaver)

        self.button_vars['f4'] = tk.BooleanVar(value=False)
        self.button4 = PushButton(self.root, {
            'x': 50,
            'y': 260,
            'width': 120,
            'height': 40,
            'text': 'F4',
            'variable': self.button_vars['f4'],
            'label': 'F4',
            'label_pos': 'top'
        }, self.autosaver)

        #Sliders for channel 1
        self.slider_vars['slide_x_ch1'] = tk.DoubleVar(value=0.0)
        self.slider1 = ConfigurableSlider(self.root, {
            'x': 200,
            'y': 60,
            'width': 300,
            'height': 30,
            'min_val': 0,
            'max_val': 255,
            'variable': self.slider_vars['slide_x_ch1'],
            'label': 'X_slider_ch1',
            'label_pos': 'top',
            'resolution': 1
        }, self.autosaver)

        self.slider_vars['zoom_x_ch1'] = tk.DoubleVar(value=0.0)
        self.slider2 = ConfigurableSlider(self.root, {
            'x': 200,
            'y': 140,
            'width': 300,
            'height': 30,
            'min_val': 0,
            'max_val': 255,
            'variable': self.slider_vars['zoom_x_ch1'],
            'label': 'Zoom_x_ch1',
            'label_pos': 'top',
            'resolution': 1
        }, self.autosaver)

        self.slider_vars['slide_x_ch2'] = tk.DoubleVar(value=0.0)
        self.slider3 = ConfigurableSlider(self.root, {
            'x': 200,
            'y': 220,
            'width': 300,
            'height': 30,
            'min_val': 0,
            'max_val': 255,
            'variable': self.slider_vars['slide_x_ch2'],
            'label': 'X_slider_ch2',
            'label_pos': 'top',
            'resolution': 1
        }, self.autosaver)
        
        self.slider_vars['zoom_x_ch2'] = tk.DoubleVar(value=0.0)
        self.slider4 = ConfigurableSlider(self.root, {
            'x': 200,
            'y': 300,
            'width': 300,
            'height': 30,
            'min_val': 0,
            'max_val': 255,
            'variable': self.slider_vars['zoom_x_ch2'],
            'label': 'Zoom_x_ch2',
            'label_pos': 'top',
            'resolution': 1
        }, self.autosaver)
        
        #Sliders for channel 2
        self.slider_vars['slide_y_ch2'] = tk.DoubleVar(value=0.0)
        self.slider3 = ConfigurableSlider(self.root, {
            'x': 530,
            'y': 60,
            'width': 300,
            'height': 30,
            'min_val': 0,
            'max_val': 255,
            'variable': self.slider_vars['slide_y_ch2'],
            'label': 'Y_slider_ch2',
            'label_pos': 'top',
            'resolution': 1
        }, self.autosaver)
        
        self.slider_vars['zoom_y_ch2'] = tk.DoubleVar(value=0.0)
        self.slider4 = ConfigurableSlider(self.root, {
            'x': 530,
            'y': 140,
            'width': 300,
            'height': 30,
            'min_val': 0,
            'max_val': 255,
            'variable': self.slider_vars['zoom_y_ch2'],
            'label': 'Zoom_y_ch2',
            'label_pos': 'top',
            'resolution': 1
        }, self.autosaver)

        #Buttons
        self.button_vars['Pause'] = tk.BooleanVar(value=False)
        self.button1 = ConfigurableButton(self.root, {
            'x': 860,
            'y': 60,
            'width': 120,
            'height': 40,
            'text': 'Pause',
            'variable': self.button_vars['Pause'],
            'label': 'Pause',
            'label_pos': 'top'
        }, self.autosaver)

        self.button_vars['Cursor'] = tk.BooleanVar(value=False)
        self.button2 = ConfigurableButton(self.root, {
            'x': 860,
            'y': 120,
            'width': 120,
            'height': 40,
            'text': 'Cursor',
            'variable': self.button_vars['Cursor'],
            'label': 'Cursor',
            'label_pos': 'top'
        }, self.autosaver)

        self.button_vars['Toggle_ch'] = tk.IntVar(value=1)
        self.button3 = ToggleButton(self.root, {
            'x': 860,
            'y': 180,
            'width': 120,
            'height': 40,
            'text': 'Toggle_ch',
            'variable': self.button_vars['Toggle_ch'],
            'label': 'Toggle_ch',
            'label_pos': 'top'
        }, self.autosaver)

        self.button_vars['Reset'] = tk.BooleanVar(value=False)
        self.button4 = PushButton(self.root, {
            'x': 860,
            'y': 240,
            'width': 120,
            'height': 40,
            'text': 'Reset',
            'variable': self.button_vars['Reset'],
            'label': 'Reset',
            'label_pos': 'top'
        }, self.autosaver)

    def save_states(self):
        """Save all widget states to JSON file"""
        state = {
            'buttons': {name: var.get() for name, var in self.button_vars.items()},
            'sliders': {name: var.get() for name, var in self.slider_vars.items()}
        }
        
        try:
            # Write to temporary file first
            temp_file = 'widget_states.tmp'
            with open(temp_file, 'w') as f:
                json.dump(state, f, indent=2)
            
            # Rename temporary file to final file (atomic operation)
            if os.path.exists('widget_states.json'):
                os.remove('widget_states.json')
            os.rename(temp_file, 'widget_states.json')
            
            # self.status_var.set(f"Saved at {time.strftime('%H:%M:%S')}")
        except Exception as e:
            self.status_var.set(f"Save failed: {str(e)}")
    
    def load_states(self):
        """Load widget states from JSON file"""
        try:
            with open('widget_states.json', 'r') as f:
                state = json.load(f)
            
            # Load button states
            for name, value in state.get('buttons', {}).items():
                if name in self.button_vars:
                    self.button_vars[name].set(value)
            
            # Load slider states
            for name, value in state.get('sliders', {}).items():
                if name in self.slider_vars:
                    self.slider_vars[name].set(value)
            
            # self.status_var.set("States loaded successfully")
        except FileNotFoundError:
            self.status_var.set("No saved states found - using defaults")
        except Exception as e:
            self.status_var.set(f"Load error: {str(e)}")
    
    def on_close(self):
        """Handle window close event"""
        self.save_states()  # One final save
        self.autosaver.stop()
        self.root.destroy()
    
    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    root = tk.Tk()
    app = StateSaverApp(root)
    app.run()