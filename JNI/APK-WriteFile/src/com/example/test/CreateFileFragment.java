package com.example.test;

import java.io.File;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;

public class CreateFileFragment extends Fragment implements OnClickListener {
	private CreateFile mJNI;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		this.mJNI = new CreateFile();
		View rootView = inflater.inflate(R.layout.fragment_main, container, false);
		Button button = (Button) rootView.findViewById(R.id.create_file_btn);
		button.setOnClickListener(this);
		return rootView;
	}

	@Override
	public void onClick(View v) {
		if (v.getId() == R.id.create_file_btn) {
			this.createFile();
		}

	}

	private void createFile() {
		String filePath = this.getActivity().getFilesDir().getAbsolutePath();
		filePath += File.separator + "a.ddib";
		this.mJNI.createFile(filePath);
	}
}
